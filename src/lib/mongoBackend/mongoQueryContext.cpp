/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Fermin Galan Marquez
*/
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/sem.h"

#include "mongoBackend/MongoGlobal.h"
#include "mongoBackend/mongoQueryContext.h"

#include "ngsi/ContextRegistrationResponse.h"
#include "ngsi10/QueryContextRequest.h"
#include "ngsi10/QueryContextResponse.h"

/* ****************************************************************************
*
* someContextElementNotFound -
*
* Returns true if some attribute with 'found' set to 'false' is found in the CER vector passed
* as argument
*
*/
bool someContextElementNotFound(ContextElementResponseVector& cerV)
{
  for (unsigned int ix = 0; ix < cerV.size(); ++ix)
  {
    if (someContextElementNotFound(*cerV.get(ix)))
    {
      return true;
    }
  }
  return false;
}

/* ****************************************************************************
*
* fillContextProviders -
*
* Looks in the elements of the CER vector passed as argument, searching for a suitable CPr in the CRR
* vector passed as argument. If a suitable CPr is found, it is added to the CER (and the 'found' field
* is changed to true)
*
*/
void fillContextProviders(ContextElementResponseVector& cerV, ContextRegistrationResponseVector& crrV)
{
  for (unsigned int ix = 0; ix < cerV.size(); ++ix)
  {
    fillContextProviders(cerV.get(ix), crrV);
  }
}

/* ****************************************************************************
*
* addContextProviderEntity -
*
*/
void addContextProviderEntity(ContextElementResponseVector& cerV, EntityId* enP, ProvidingApplication pa)
{
  for (unsigned int ix = 0; ix < cerV.size(); ++ix)
  {
    if (cerV.get(ix)->contextElement.entityId.id == enP->id && cerV.get(ix)->contextElement.entityId.type == enP->type)
    {
      cerV.get(ix)->contextElement.providingApplicationList.push_back(pa);
      return;    /* by construction, no more than one CER with the same entity information should exist in the CERV) */
    }
  }

  /* Reached this point, it means that the cerV doesn't contain a proper CER, so we create it */
  ContextElementResponse* cerP            = new ContextElementResponse();
  cerP->contextElement.entityId.id        = enP->id;
  cerP->contextElement.entityId.type      = enP->type;
  cerP->contextElement.entityId.isPattern = "false";
  cerP->contextElement.providingApplicationList.push_back(pa);

  cerP->statusCode.fill(SccOk);
  cerV.push_back(cerP);

}

/* ****************************************************************************
*
* addContextProviderAttribute -
*
*
*/
void addContextProviderAttribute(ContextElementResponseVector& cerV, EntityId* enP, ContextRegistrationAttribute* craP, const ProvidingApplication& pa)
{
  for (unsigned int ix = 0; ix < cerV.size(); ++ix)
  {
    if ((cerV.get(ix)->contextElement.entityId.id != enP->id) ||
        (cerV.get(ix)->contextElement.entityId.type != enP->type))
    {
     continue;
    }

    for (unsigned int jx = 0; jx < cerV.get(ix)->contextElement.contextAttributeVector.size(); ++jx)
    {
      std::string attrName = cerV.get(ix)->contextElement.contextAttributeVector.get(jx)->name;
      if (attrName == craP->name)
      {
        /* In this case, the attribute has been already found in local database. CPr is unnecessary */
        return;
      }
    }
    /* Reached this point, no attribute was found, so adding it with corresponding CPr info */
    ContextAttribute* caP = new ContextAttribute(craP->name, "", "");
    caP->providingApplication = pa;
    cerV.get(ix)->contextElement.contextAttributeVector.push_back(caP);
    return;

  }

  /* Reached this point, it means that the cerV doesn't contain a proper CER, so we create it */
  ContextElementResponse* cerP            = new ContextElementResponse();
  cerP->contextElement.entityId.id        = enP->id;
  cerP->contextElement.entityId.type      = enP->type;
  cerP->contextElement.entityId.isPattern = "false";

  cerP->statusCode.fill(SccOk);

  ContextAttribute* caP = new ContextAttribute(craP->name, "", "");
  caP->providingApplication = pa;
  cerP->contextElement.contextAttributeVector.push_back(caP);

  cerV.push_back(cerP);
}


/* ****************************************************************************
*
* matchEntityInCrr -
*
*/
bool matchEntityInCrr(ContextRegistration& cr, EntityId* enP)
{
  for (unsigned int ix = 0; ix < cr.entityIdVector.size(); ++ix)
  {
    EntityId* crEnP = cr.entityIdVector.get(ix);
    if (matchEntity(crEnP, enP))
    {
      return true;
    }
  }
  return false;
}


/* ****************************************************************************
*
* addContextProviders -
*
* This function takes a CRR vector and adds the Context Providers in the CER vector
* (except the ones corresponding to some locally found attribute, i.e. info already in the
* CER vector)
*
* The enP parameter is optional. If not NULL, then before adding a CPr the function checks that the
* containting CRR matches the entity (this is used for funcionality related to  "generic queries", see
* processGenericEntities() function)
*
*/
void addContextProviders(ContextElementResponseVector& cerV, ContextRegistrationResponseVector& crrV, EntityId* enP = NULL)
{
  for (unsigned int ix = 0; ix < crrV.size(); ++ix)
  {
    ContextRegistration cr = crrV.get(ix)->contextRegistration;

    /* In the case a "filtering" entity was provided, check that the current CRR matches or skip to next CRR */
    if (enP != NULL && !matchEntityInCrr(cr, enP)) {
      continue;
    }

    if (cr.contextRegistrationAttributeVector.size() == 0)
    {
      /* Registration without attributes */
      for (unsigned int jx = 0; jx < cr.entityIdVector.size(); ++jx)
      {
        addContextProviderEntity(cerV, cr.entityIdVector.get(jx), cr.providingApplication);
      }
    }
    else
    {
      /* Registration with attributes */
      for (unsigned int eIx = 0; eIx < cr.entityIdVector.size(); ++eIx)
      {
        for (unsigned int aIx = 0; aIx < cr.contextRegistrationAttributeVector.size(); ++aIx)
        {
          addContextProviderAttribute(cerV, cr.entityIdVector.get(eIx), cr.contextRegistrationAttributeVector.get(aIx), cr.providingApplication);
        }
      }
    }
  }
}

/* ****************************************************************************
*
* processGenericEntities -
*
* If the request included some "generic" entity, some additional CPr could be needed in the CER array. There are
* three cases of "generic" entities: 1) not pattern + null type, 2) pattern + not null type, 3) pattern + null type
*
*/
void processGenericEntities(EntityIdVector& enV, ContextElementResponseVector& cerV, ContextRegistrationResponseVector& crrV)
{
  for (unsigned int ix = 0; ix < enV.size(); ++ix)
  {
    EntityId* enP = enV.get(ix);
    if (enP->type == "" || isTrue(enP->isPattern))
    {
      addContextProviders(cerV, crrV, enP);
    }
  }
}

/* ****************************************************************************
*
* mongoQueryContext - 
*
* NOTE
*   If the in/out-parameter countP is non-NULL then the number of matching entities
*   must be returned in *countP.
*
*   This replaces the 'uriParams[URI_PARAM_PAGINATION_DETAILS]' way of passing this information.
*   The old method was one-way, using the new method 
*/
HttpStatusCode mongoQueryContext
(
  QueryContextRequest*                 requestP,
  QueryContextResponse*                responseP,
  const std::string&                   tenant,
  const std::vector<std::string>&      servicePathV,
  std::map<std::string, std::string>&  uriParams,
  long long*                           countP
)
{
    int         offset         = atoi(uriParams[URI_PARAM_PAGINATION_OFFSET].c_str());
    int         limit          = atoi(uriParams[URI_PARAM_PAGINATION_LIMIT].c_str());
    std::string detailsString  = uriParams[URI_PARAM_PAGINATION_DETAILS];
    bool        details        = (strcasecmp("on", detailsString.c_str()) == 0)? true : false;

    LM_T(LmtMongo, ("QueryContext Request"));    
    LM_T(LmtPagination, ("Offset: %d, Limit: %d, Details: %s", offset, limit, (details == true)? "true" : "false"));

    /* FIXME: restriction not supported for the moment */
    if (!requestP->restriction.attributeExpression.isEmpty())
    {
      LM_W(("Bad Input (restriction found, but restrictions are not supported by mongo backend)"));
    }

    std::string err;
    bool        ok;
    bool        reqSemTaken;

    ContextElementResponseVector rawCerV;

    reqSemTake(__FUNCTION__, "ngsi10 query request", SemReadOp, &reqSemTaken);
    ok = entitiesQuery(requestP->entityIdVector,
                       requestP->attributeList,
                       requestP->restriction,
                       &rawCerV,
                       &err,
                       true,
                       tenant,
                       servicePathV,
                       offset,
                       limit,
                       countP);
    reqSemGive(__FUNCTION__, "ngsi10 query request", reqSemTaken);

    if (!ok)
    {
        responseP->errorCode.fill(SccReceiverInternalError, err);
        rawCerV.release();
        return SccOk;
    }

    ContextRegistrationResponseVector crrV;

    /* In the case of empty response, if only generic processing is needed */
    if (rawCerV.size() == 0)
    {
      if (registrationsQuery(requestP->entityIdVector, requestP->attributeList, &crrV, &err, tenant, servicePathV, 0, 0, false))
      {
        if (crrV.size() > 0)
        {
          processGenericEntities(requestP->entityIdVector, rawCerV, crrV);
        }
      }
      else
      {
        /* Different from errors in DB at entitiesQuery(), DB fails at registrationsQuery() are not considered "critical" */
        LM_E(("Database Error (%s)", err.c_str()));
      }
      crrV.release();
    }

    /* First CPr lookup (in the case some CER is not found): looking in E-A registrations */
    if (someContextElementNotFound(rawCerV))
    {
      if (registrationsQuery(requestP->entityIdVector, requestP->attributeList, &crrV, &err, tenant, servicePathV, 0, 0, false))
      {
        if (crrV.size() > 0)
        {
          fillContextProviders(rawCerV, crrV);
          processGenericEntities(requestP->entityIdVector, rawCerV, crrV);
        }
      }
      else
      {
        /* Different from errors in DB at entitiesQuery(), DB fails at registrationsQuery() are not considered "critical" */
        LM_E(("Database Error (%s)", err.c_str()));
      }
      crrV.release();
    }

    /* Second CPr lookup (in the case some element stills not being found): looking in E-<null> registrations */
    AttributeList attrNullList;
    if (someContextElementNotFound(rawCerV))
    {
      if (registrationsQuery(requestP->entityIdVector, attrNullList, &crrV, &err, tenant, servicePathV, 0, 0, false))
      {
        if (crrV.size() > 0)
        {
          fillContextProviders(rawCerV, crrV);
        }
      }
      else
      {
        /* Different from errors in DB at entitiesQuery(), DB fails at registrationsQuery() are not considered "critical" */
        LM_E(("Database Error (%s)", err.c_str()));
      }
      crrV.release();
    }

    /* Special case: request with <null> attributes. In that case, entitiesQuery() may have captured some local attribute, but
     * the list need to be completed. Note that in the case of having this request someContextElementNotFound() is always false
     * so we efficient not invoking registrationQuery() too much times */
    if (requestP->attributeList.size() == 0)
    {
      if (registrationsQuery(requestP->entityIdVector, requestP->attributeList, &crrV, &err, tenant, servicePathV, 0, 0, false))
      {
        if (crrV.size() > 0)
        {
          addContextProviders(rawCerV, crrV);
        }
      }
      else
      {
        /* Different from fails in DB at entitiesQuery(), DB fails at registrationsQuery() are not considered "critical" */
        LM_E(("Database Error (%s)", err.c_str()));
      }
      crrV.release();
    }

    /* Prune "not found" CERs */
    pruneContextElements(rawCerV, &responseP->contextElementResponseVector);

    /* Pagination stuff */
    if (responseP->contextElementResponseVector.size() == 0)
    {

      // If the query has an empty response, we have to fill in the status code part in the response.
      //
      // However, if the response was empty due to a too high pagination offset,
      // and if the user has asked for 'details' (as URI parameter, then the response should include information about
      // the number of hits without pagination.
      //

      if ((countP != NULL) && (*countP > 0) && (offset >= *countP))
      {
        char details[256];

        snprintf(details, sizeof(details), "Number of matching entities: %lld. Offset is %d", *countP, offset);
        responseP->errorCode.fill(SccContextElementNotFound, details);
      }
      else
      {
        responseP->errorCode.fill(SccContextElementNotFound);
      }
    }
    else if (countP != NULL)
    {
      //
      // If all was OK, but the details URI param was set to 'on', then the responses error code details
      // 'must' contain the total count of hits.
      //

      char details[64];

      snprintf(details, sizeof(details), "Count: %lld", *countP);
      responseP->errorCode.fill(SccOk, details);
    }

    rawCerV.release();
    return SccOk;
}
