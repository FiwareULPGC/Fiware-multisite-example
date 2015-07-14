/*
*
* Copyright 2014 Telefonica Investigacion y Desarrollo, S.A.U
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
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "rest/uriParamNames.h"
#include "rest/EntityTypeInfo.h"
#include "convenience/AppendContextElementRequest.h"
#include "convenience/AppendContextElementResponse.h"
#include "serviceRoutines/postUpdateContext.h"
#include "serviceRoutines/postAllEntitiesWithTypeAndId.h"



/* ****************************************************************************
*
* postAllEntitiesWithTypeAndId - 
*
* POST /v1/contextEntities/type/{entity::type}/id/{entity::id}
*
* Payload In:  AppendContextElementRequest
* Payload Out: AppendContextElementResponse
*
* URI parameters:
*   - attributesFormat=object
*   - entity::type=TYPE (must coincide with type in URL-path)
*   - !exist=entity::type  (if set - error -- entity::type cannot be empty)
*   - exist=entity::type   (not supported - ok if present, ok if not present ...)
*
* NOTE:
*   This service routine responds with an error if any part of the EntityId in
*   the payload is filled in.
*
* 01. Get values from URL (entityId::type, exist, !exist)
* 02. Check that the entity is NOT filled in in the payload
* 03. Check validity of URI params
* 04. Fill in UpdateContextRequest
* 05. Call Standard Operation
* 06. Fill in response from UpdateContextReSponse
* 07. Cleanup and return result
*/
std::string postAllEntitiesWithTypeAndId
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string                   entityType            = compV[3];
  std::string                   entityId              = compV[5];
  EntityTypeInfo                typeInfo              = EntityTypeEmptyOrNotEmpty;
  std::string                   typeNameFromUriParam  = ciP->uriParam[URI_PARAM_ENTITY_TYPE];
  AppendContextElementRequest*  reqP                  = &parseDataP->acer.res;
  std::string                   answer;
  AppendContextElementResponse  response;

  // FIXME P1: AttributeDomainName skipped
  // FIXME P1: domainMetadataVector skipped


  // 01. Get values from URL (entityId::type, esist, !exist)
  if (ciP->uriParam[URI_PARAM_NOT_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeEmpty;
  }
  else if (ciP->uriParam[URI_PARAM_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeNotEmpty;
  }


  // 02. Check that the entity is NOT filled in in the payload
  if ((reqP->entity.id != "") || (reqP->entity.type != "") || (reqP->entity.isPattern != ""))
  {
    LM_W(("Bad Input (unknown field)"));
    response.errorCode.fill(SccBadRequest, "invalid payload: unknown fields");
    return response.render(ciP, IndividualContextEntity, "");
  }


  // 03. Check validity of URI params
  if (typeInfo == EntityTypeEmpty)
  {
    LM_W(("Bad Input (entity::type cannot be empty for this request)"));

    response.errorCode.fill(SccBadRequest, "entity::type cannot be empty for this request");
    response.entity.fill(entityId, entityType, "false");

    answer = response.render(ciP, AllEntitiesWithTypeAndId, "");

    parseDataP->acer.res.release();
    return answer;
  }
  else if ((typeNameFromUriParam != entityType) && (typeNameFromUriParam != ""))
  {
    LM_W(("Bad Input non-matching entity::types in URL"));

    response.errorCode.fill(SccBadRequest, "non-matching entity::types in URL");
    response.entity.fill(entityId, entityType, "false");

    answer = response.render(ciP, AllEntitiesWithTypeAndId, "");

    parseDataP->acer.res.release();
    return answer;
  }

  // Now, forward Entity to response
  response.entity.fill(entityId, entityType, "false");


  // 04. Fill in UpdateContextRequest
  parseDataP->upcr.res.fill(&parseDataP->acer.res, entityId, entityType);


  // 05. Call Standard Operation
  answer = postUpdateContext(ciP, components, compV, parseDataP);


  // 06. Fill in response from UpdateContextReSponse
  response.fill(&parseDataP->upcrs.res, entityId, entityType);


  // 07. Cleanup and return result
  answer = response.render(ciP, IndividualContextEntity, "");
  parseDataP->upcr.res.release();
  response.release();

  return answer;
}