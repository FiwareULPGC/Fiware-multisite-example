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
#include "ngsi/Throttling.h"



/* ****************************************************************************
*
* Throttling::Throttling
*
* Explicit constructor needed to initialize primitive types so they don't get
* random values from the stack
*/
Throttling::Throttling()
{
  seconds = 0;
}



/* ****************************************************************************
*
* Throttling::parse -
*/
int64_t Throttling::parse(void)
{
  seconds = parse8601(string);
  return seconds;
}



/* ****************************************************************************
*
* Throttling::check -
*/
std::string Throttling::check
(
  RequestType         requestType,
  Format              format,
  const std::string&  indent,
  const std::string&  predetectedError,
  int                 counter
)
{
  // FIXME - make Throttling and Duration inherit from same class
  //         that implements the 'parse' method

  if (string == "")
  {
    return "OK";
  }

  if (parse() == -1)
  {
    return "syntax error in throttling string";
  }

  return "OK";
}



/* ****************************************************************************
*
* Throttling::isEmpty -
*/
bool Throttling::isEmpty(void)
{
  return (string == "")? true : false;
}



/* ****************************************************************************
*
* Throttling::set -
*/
void Throttling::set(const std::string& value)
{
  string = value;
}



/* ****************************************************************************
*
* Throttling::get -
*/
std::string Throttling::get(void)
{
  return string;
}



/* ****************************************************************************
*
* Throttling::present -
*/
void Throttling::present(const std::string& indent)
{
  if (string != "")
  {
    LM_F(("%sThrottling: %s\n", indent.c_str(), string.c_str()));
  }
  else
  {
    LM_F(("%sNo Throttling\n", indent.c_str()));
  }
}



/* ****************************************************************************
*
* Throttling::render -
*/
std::string Throttling::render(Format format, const std::string& indent, bool comma)
{
  if (string == "")
  {
    return "";
  }

  return valueTag(indent, "throttling", string, format, comma);
}
