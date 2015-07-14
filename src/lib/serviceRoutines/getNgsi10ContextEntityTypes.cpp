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
#include "serviceRoutines/postQueryContext.h"
#include "serviceRoutines/getNgsi10ContextEntityTypes.h"



/* ****************************************************************************
*
* getNgsi10ContextEntityTypes - 
*
* GET /v1/contextEntityTypes/{entity::type}
* GET /ngsi10/contextEntityTypes/{entity::type}
*
* Payload In:  None
* Payload Out: QueryContextResponse
*
* URI parameters:
*   - attributesFormat=object
*   - entity::type=XXX     (must coincide with entity::type in URL)
*   - !exist=entity::type  (if set - error -- entity::type cannot be empty)
*   - exist=entity::type   (not supported - ok if present, ok if not present ...)
*
* 01. Get values from URL (entityId::type, esist, !exist)
* 02. Check validity of URI params
* 03. Fill in QueryContextRequest
* 04. Call standard operation postQueryContext (that renders the QueryContextResponse)
* 05. If 404 Not Found - enter request entityId::type into response context element
* 06. Cleanup and return result
*/
std::string getNgsi10ContextEntityTypes
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string     answer;
  std::string     typeName              = compV[2];
  EntityTypeInfo  typeInfo              = EntityTypeEmptyOrNotEmpty;
  std::string     typeNameFromUriParam  = ciP->uriParam[URI_PARAM_ENTITY_TYPE];


  // 01. Get values from URL (entityId::type, esist, !exist)
  if (ciP->uriParam[URI_PARAM_NOT_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeEmpty;
  }
  else if (ciP->uriParam[URI_PARAM_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeNotEmpty;
  }


  // 02. Check validity of URI params
  if (typeInfo == EntityTypeEmpty)
  {
    parseDataP->qcrs.res.errorCode.fill(SccBadRequest, "entity::type cannot be empty for this request");
    LM_W(("Bad Input (entity::type cannot be empty for this request)"));
    answer = parseDataP->qcrs.res.render(ciP, Ngsi10ContextEntityTypes, "");
    parseDataP->qcr.res.release();
    return answer;
  }
  else if ((typeNameFromUriParam != typeName) && (typeNameFromUriParam != ""))
  {
    parseDataP->qcrs.res.errorCode.fill(SccBadRequest, "non-matching entity::types in URL");
    LM_W(("Bad Input non-matching entity::types in URL"));
    answer = parseDataP->qcrs.res.render(ciP, Ngsi10ContextEntityTypes, "");
    parseDataP->qcr.res.release();
    return answer;
  }


  // 03. Fill in QueryContextRequest
  parseDataP->qcr.res.fill(".*", typeName, "");


  // 04. Call standard operation postQueryContext (that renders the QueryContextResponse)
  answer = postQueryContext(ciP, components, compV, parseDataP);


  // 05. If 404 Not Found - enter request entityId::type into response context element
  if (parseDataP->qcrs.res.errorCode.code == SccContextElementNotFound)
  {
    parseDataP->qcrs.res.errorCode.details = std::string("entityId::type /") + typeName + "/ non-existent";
    answer = parseDataP->qcrs.res.render(ciP, Ngsi10ContextEntityTypes, "");
  }


  // 06. Cleanup and return result
  parseDataP->qcr.res.release();
  return answer;
}