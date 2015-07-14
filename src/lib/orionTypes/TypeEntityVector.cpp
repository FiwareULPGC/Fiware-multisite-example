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
#include <stdio.h>
#include <map>
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/Request.h"
#include "rest/ConnectionInfo.h"
#include "orionTypes/TypeEntity.h"
#include "orionTypes/TypeEntityVector.h"



/* ****************************************************************************
*
* TypeEntityVector::TypeEntityVector -
*/
TypeEntityVector::TypeEntityVector()
{
  vec.clear();
}


/* ****************************************************************************
*
* TypeEntityVector::render -
*/
std::string TypeEntityVector::render
(
  ConnectionInfo*     ciP,
  const std::string&  indent,
  bool                comma
)
{
  std::string out      = "";
  std::string xmlTag   = "typeEntities";
  std::string jsonTag  = "types";


  if (vec.size() > 0)
  {

    out += startTag(indent, xmlTag, jsonTag, ciP->outFormat, true, true);

    for (unsigned int ix = 0; ix < vec.size(); ++ix)
    {
      out += vec[ix]->render(ciP, indent + "  ", ix != vec.size() - 1);
    }
    out += endTag(indent, xmlTag, ciP->outFormat, comma, true);
  }

  return out;
}



/* ****************************************************************************
*
* TypeEntityVector::check -
*/
std::string TypeEntityVector::check
(
  ConnectionInfo*     ciP,
  const std::string&  indent,
  const std::string&  predetectedError
)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    std::string res;

    if ((res = vec[ix]->check(ciP, indent, predetectedError)) != "OK")
    {
     return res;
    }
  }

  return "OK";
}



/* ****************************************************************************
*
* TypeEntityVector::present -
*/
void TypeEntityVector::present(const std::string& indent)
{
  LM_F(("%lu TypeEntitys", (uint64_t) vec.size()));

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->present(indent);
  }
}



/* ****************************************************************************
*
* TypeEntityVector::push_back -
*/
void TypeEntityVector::push_back(TypeEntity* item)
{
  vec.push_back(item);
}



/* ****************************************************************************
*
* TypeEntityVector::get -
*/
TypeEntity* TypeEntityVector::get(unsigned int ix)
{
  if (ix < vec.size())
    return vec[ix];
  return NULL;
}



/* ****************************************************************************
*
* TypeEntityVector::size -
*/
unsigned int TypeEntityVector::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* TypeEntityVector::release -
*/
void TypeEntityVector::release(void)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->release();
    delete vec[ix];
  }

  vec.clear();
}
