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
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/ConditionValueList.h"



/* ****************************************************************************
*
* render - 
*/
std::string ConditionValueList::render(Format format, const std::string& indent, bool comma)
{
  std::string  out = "";
  std::string  tag = "condValueList";

  if (vec.size() == 0)
    return "";

  out += startTag(indent, tag, tag, format, true, true);

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
    out += valueTag(indent + "  ", "condValue", "", vec[ix], format, ix != vec.size() - 1);

  out += endTag(indent, tag, format, comma, true);

  return out;
}



/* ****************************************************************************
*
* ConditionValueList::check - 
*/
std::string ConditionValueList::check
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
    if (vec[ix] == "")
      return "empty condValue name";
  }

  return "OK";
}



/* ****************************************************************************
*
* ConditionValueList::present - 
*/
void ConditionValueList::present(const std::string& indent)
{
  LM_F(("%sConditionValue List\n",    indent.c_str()));

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
    LM_F(("%s  %s\n", indent.c_str(), vec[ix].c_str()));
}



/* ****************************************************************************
*
* ConditionValueList::release - 
*/
void ConditionValueList::release(void)
{
  vec.clear();
}



/* ****************************************************************************
*
* push_back - 
*/
void ConditionValueList::push_back(const std::string& attributeName)
{
  vec.push_back(attributeName);
}



/* ****************************************************************************
*
* ConditionValueList::size - 
*/
unsigned int ConditionValueList::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* ConditionValueList::get - 
*/
std::string ConditionValueList::get(int ix)
{
  return vec[ix];
}
