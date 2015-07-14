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
#include <stdio.h>
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/ContextRegistrationResponseVector.h"



/* ****************************************************************************
*
* ContextRegistrationResponseVector::push_back -
*/
void ContextRegistrationResponseVector::push_back(ContextRegistrationResponse* item)
{
  vec.push_back(item);
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::render -
*/
std::string ContextRegistrationResponseVector::render(Format format, const std::string& indent, bool comma)
{
  std::string  out     = "";
  std::string  xmlTag  = "contextRegistrationResponseList";
  std::string  jsonTag = "contextRegistrationResponses";

  if (vec.size() == 0)
  {
    return "";
  }

  out += startTag(indent, xmlTag, jsonTag, format, true, true);

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
     out += vec[ix]->render(format, indent + "  ", (ix != vec.size() - 1));
  }

  out += endTag(indent, xmlTag, format, comma, true);

  return out;
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::present -
*/
void ContextRegistrationResponseVector::present(const std::string& indent)
{
  LM_F(("%lu ContextRegistrationResponses", (uint64_t) vec.size()));

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->present(indent);
  }
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::release -
*/
void ContextRegistrationResponseVector::release(void)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->release();
    delete(vec[ix]);
  }

  vec.clear();
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::get -
*/
ContextRegistrationResponse* ContextRegistrationResponseVector::get(int ix)
{
  return vec[ix];
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::size -
*/
unsigned int ContextRegistrationResponseVector::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* ContextRegistrationResponseVector::check -
*/
std::string ContextRegistrationResponseVector::check
(
  RequestType         requestType,
  Format              format,
  const std::string&  indent,
  const std::string&  predetectedError,
  int                 counter
)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    std::string res;

    if ((res = vec[ix]->check(requestType, format, indent, predetectedError, counter)) != "OK")
    {
      return res;
    }
  }

  return "OK";
}
