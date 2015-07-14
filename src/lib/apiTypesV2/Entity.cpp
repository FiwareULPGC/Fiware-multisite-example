/*
*
* Copyright 2015 Telefonica Investigacion y Desarrollo, S.A.U
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

#include "common/tag.h"
#include "apiTypesV2/Entity.h"
#include "ngsi10/QueryContextResponse.h"



/* ****************************************************************************
*
* Entity::Entity - 
*/
Entity::Entity()
{
}



/* ****************************************************************************
*
* Entity::~Entity - 
*/
Entity::~Entity()
{
  release();
}


/* ****************************************************************************
*
* Entity::render - 
*/
std::string Entity::render(ConnectionInfo* ciP, RequestType requestType, bool comma)
{

  if ((errorCode.description == "") && ((errorCode.error == "OK") || (errorCode.error == "")))
  {
      std::string out = "{";

      out += JSON_VALUE("id", id);

      if (type != "")
      {
        out += ",";
        out += JSON_VALUE("type", type);
      }

      if (attributeVector.size() != 0)
      {
        out += ",";
        out += attributeVector.toJson(true);
      }

      out += "}";

      if (comma)
      {
        out += ",";
      }

      return out;
  }

  return errorCode.toJson(true);

}



/* ****************************************************************************
*
* Entity::check - 
*/
std::string Entity::check(ConnectionInfo* ciP, RequestType requestType)
{
  if (id == "")
  {
    return "No Entity ID";
  }

  return "OK";
}



/* ****************************************************************************
*
* Entity::present - 
*/
void Entity::present(const std::string& indent)
{
  LM_F(("%sid:        %s", indent.c_str(), id.c_str()));
  LM_F(("%stype:      %s", indent.c_str(), type.c_str()));
  LM_F(("%sisPattern: %s", indent.c_str(), isPattern.c_str()));

  attributeVector.present(indent + "  ");
}



/* ****************************************************************************
*
* Entity::fill - 
*/
void Entity::fill(const std::string& _id, const std::string& _type, const std::string& _isPattern, ContextAttributeVector* aVec)
{
  id         = _id;
  type       = _type;
  isPattern  = _isPattern;

  attributeVector.fill(aVec);
}

void Entity::fill(QueryContextResponse* qcrsP)
{

  if (qcrsP->errorCode.code == SccContextElementNotFound)
  {
    errorCode.fill("NotFound",  "The requested entity has not been found. Check type and id");
  }
  else if (qcrsP->errorCode.code != SccOk)
  {
    //
    // any other error distinct from Not Found
    //
    errorCode.fill(qcrsP->errorCode);
  }
  else if (qcrsP->contextElementResponseVector.size() > 1) // qcrsP->errorCode.code == SccOk
  {
      //
      // If there are more than one entity, we return an error
      //
      errorCode.fill("TooManyResults", "There is more than one entity with that id. Refine your query.");
  }
  else
  {
    ContextElement* ceP = &qcrsP->contextElementResponseVector[0]->contextElement;
    fill(ceP->entityId.id, ceP->entityId.type, ceP->entityId.isPattern, &ceP->contextAttributeVector);
  }
}

/* ****************************************************************************
*
* Entity::release - 
*/
void Entity::release(void)
{
  attributeVector.release();
}
