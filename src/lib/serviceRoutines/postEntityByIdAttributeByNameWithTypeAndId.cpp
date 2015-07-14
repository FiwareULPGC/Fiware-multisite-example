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
#include "ngsi9/RegisterContextRequest.h"
#include "rest/ConnectionInfo.h"
#include "rest/EntityTypeInfo.h"
#include "rest/uriParamNames.h"
#include "serviceRoutines/postRegisterContext.h"
#include "serviceRoutines/postEntityByIdAttributeByNameWithTypeAndId.h"



/* ****************************************************************************
*
* postEntityByIdAttributeByNameWithTypeAndId - 
*
* POST /v1/registry/contextEntities/type/{entity::type}/id/{entity::id}/attributes/{attribute::name}
*
* Payload In:  RegisterProviderRequest
* Payload Out: RegisterContextResponse
*
* URI parameters:
*   - entity::type=XXX     (must coincide with entity::type in URL)
*   - !exist=entity::type  (if set - error -- entity::type cannot be empty)
*   - exist=entity::type   (not supported - ok if present, ok if not present ...)
*
* 01. Get values from URL (entityId::type, exist, !exist)
* 02. Check validity of URI params
* 03. Fill in RegisterContextRequest
* 04. Call standard operation postRegisterContext
* 05. Cleanup and return result
*/
std::string postEntityByIdAttributeByNameWithTypeAndId
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string     entityType              = compV[4];
  std::string     entityId                = compV[6];
  std::string     attributeName           = compV[8];
  std::string     entityTypeFromUriParam  = ciP->uriParam[URI_PARAM_ENTITY_TYPE];
  EntityTypeInfo  typeInfo                = EntityTypeEmptyOrNotEmpty;
  std::string     answer;


  // 01. Get values from URL (entityId::type, exist, !exist)
  if (ciP->uriParam[URI_PARAM_NOT_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeEmpty;
  }
  else if (ciP->uriParam[URI_PARAM_EXIST] == URI_PARAM_ENTITY_TYPE)
  {
    typeInfo = EntityTypeNotEmpty;
  }


  //
  // 02. Check validity of URI params ...
  //     and if OK:
  // 03. Fill in RegisterContextRequest
  // 04. Call standard operation postRegisterContext
  //
  if (typeInfo == EntityTypeEmpty)
  {
    parseDataP->rcrs.res.errorCode.fill(SccBadRequest, "entity::type cannot be empty for this request");
    LM_W(("Bad Input (entity::type cannot be empty for this request)"));
    answer = parseDataP->rcrs.res.render(IndividualContextEntityAttributeWithTypeAndId, ciP->outFormat, "");
  }
  else if ((entityTypeFromUriParam != entityType) && (entityTypeFromUriParam != ""))
  {
    parseDataP->rcrs.res.errorCode.fill(SccBadRequest, "non-matching entity::types in URL");
    LM_W(("Bad Input non-matching entity::types in URL"));
    answer = parseDataP->rcrs.res.render(IndividualContextEntityAttributeWithTypeAndId, ciP->outFormat, "");
  }
  else
  {
    // 03. Fill in RegisterContextRequest
    parseDataP->rcr.res.fill(parseDataP->rpr.res, entityId, entityType, attributeName);

    // 04. Call standard operation postRegisterContext
    answer = postRegisterContext(ciP, components, compV, parseDataP);
  }


  // 05. Cleanup and return result
  parseDataP->rpr.res.release();
  parseDataP->rcr.res.release();

  return answer;
}
