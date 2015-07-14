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

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/Request.h"
#include "ngsi/Reference.h"



/* ****************************************************************************
*
* Reference::check -
*/
std::string Reference::check
(
  RequestType         requestType,
  Format              format,
  const std::string&  indent,
  const std::string&  predetectedError,
  int                 counter
)
{
  if (string == "")
  {
    if ((requestType == SubscribeContextAvailability) || (requestType == SubscribeContext))
    {
      return "Empty Reference";
    }
  }

  return "OK";
}



/* ****************************************************************************
*
* Reference::isEmpty -
*/
bool Reference::isEmpty(void)
{
  return (string == "")? true : false;
}



/* ****************************************************************************
*
* Reference::set -
*/
void Reference::set(const std::string& value)
{
  string = value;
}



/* ****************************************************************************
*
* Reference::get -
*/
std::string Reference::get(void)
{
  return string;
}



/* ****************************************************************************
*
* Reference::present -
*/
void Reference::present(const std::string& indent)
{
  if (string != "")
  {
    LM_F(("%sReference: %s\n", indent.c_str(), string.c_str()));
  }
  else
  {
    LM_F(("%sNo Reference\n", indent.c_str()));
  }
}



/* ****************************************************************************
*
* Reference::render -
*/
std::string Reference::render(Format format, const std::string& indent, bool comma)
{
  if (string == "")
  {
    return "";
  }

  return valueTag(indent, "reference", string, format, comma);
}



/* ****************************************************************************
*
* Reference::c_str -
*/
const char* Reference::c_str(void)
{
  return string.c_str();
}
