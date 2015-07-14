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
#include "serviceRoutines/postDiscoverContextAvailability.h"
#include "serviceRoutines/getEntityByIdAttributeByName.h"



/* ****************************************************************************
*
* getEntityByIdAttributeByName -
*
* GET /v1/registry/contextEntities/{entityId::id}/attributes/{attributeName}
* GET /ngsi9/contextEntities/{entityId::id}/attributes/{attributeName}
*
* Payload In:  None
* Payload Out: DiscoverContextAvailabilityResponse
*/
std::string getEntityByIdAttributeByName
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string                          entityId      = (compV[0] == "v1")? compV[3] : compV[2];
  std::string                          attributeName = (compV[0] == "v1")? compV[5] : compV[4];
  std::string                          answer;

  //
  // 1. Fill in parseDataP->dcar.res to pass to postDiscoverContextAvailability
  //
  EntityId                             eId(entityId, "", "");
  std::vector<std::string>             attributeV;
  Restriction                          restriction;

  attributeV.push_back(attributeName);

  parseDataP->dcar.res.fill(eId, attributeV, restriction);


  //
  // 2. Call the standard operation 
  //
  answer = postDiscoverContextAvailability(ciP, components, compV, parseDataP);

  return answer;
}