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
#include "ngsi/EntityIdVector.h"
#include "ngsi/Request.h"


/* ****************************************************************************
*
* EntityIdVector::render -
*/
std::string EntityIdVector::render(Format format, const std::string& indent, bool comma)
{
  std::string out     = "";
  std::string xmlTag  = "entityIdList";
  std::string jsonTag = "entities";

  if (vec.size() == 0)
    return "";

  out += startTag(indent, xmlTag, jsonTag, format, true, true);
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
    out += vec[ix]->render(format, indent + "  ", ix != vec.size() - 1, true);

  out += endTag(indent, xmlTag, format, comma, true);

  return out;
}



/* ****************************************************************************
*
* EntityIdVector::check -
*/
std::string EntityIdVector::check
(
  RequestType         requestType,
  Format              format,
  const std::string&  indent,
  const std::string&  predetectedError,
  int                 counter
)
{
  // Only OK to be empty if part of a ContextRegistration
  if ((requestType == DiscoverContextAvailability)           ||
      (requestType == SubscribeContextAvailability)          ||
      (requestType == UpdateContextAvailabilitySubscription) ||
      (requestType == QueryContext)                          ||
      (requestType == SubscribeContext))
  {
    if (vec.size() == 0)
    {
      LM_W(("Bad Input (mandatory entity list missing)"));
      return "No entities";
    }
  }

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    std::string res;

    if ((res = vec[ix]->check(requestType, format, indent, predetectedError, counter)) != "OK")
    {
      LM_W(("Bad Input (invalid vector of EntityIds)"));
      return res;
    }
  }

  return "OK";
}



/* ****************************************************************************
*
* EntityIdVector::present -
*/
void EntityIdVector::present(const std::string& indent)
{
  LM_F(("%lu EntityIds:\n", (uint64_t) vec.size()));

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->present(indent, ix);
  }
}



/* ****************************************************************************
*
* EntityIdVector::lookup - find a matching entity in the entity-vector
*/
EntityId* EntityIdVector::lookup(const std::string& id, const std::string& type, const std::string& isPattern)
{
  //
  // isPattern:  "false" or "" is the same
  //
  std::string isPatternFromParam = isPattern;
  if (isPatternFromParam == "")
  {
    isPatternFromParam = "false";
  }

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    std::string isPatternFromVec = vec[ix]->isPattern;

    if (isPatternFromVec == "")
    {
      isPatternFromVec = "false";
    }

    if ((vec[ix]->id == id) && (vec[ix]->type == type) && (isPatternFromVec == isPatternFromParam))
    {
      return vec[ix];
    }
  }

  return NULL;
}



/* ****************************************************************************
*
* EntityIdVector::push_back -
*/
void EntityIdVector::push_back(EntityId* item)
{
  vec.push_back(item);
}



/* ****************************************************************************
*
* EntityIdVector::push_back_if_absent -
*/
void EntityIdVector::push_back_if_absent(EntityId* item)
{
  if (lookup(item->id, item->type, item->isPattern) == NULL)
  {
    vec.push_back(item);
  }
}


/* ****************************************************************************
*
* EntityIdVector::get -
*/
EntityId* EntityIdVector::get(int ix)
{
  return vec[ix];
}



/* ****************************************************************************
*
* EntityIdVector::size -
*/
unsigned int EntityIdVector::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* EntityIdVector::release -
*/
void EntityIdVector::release(void)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->release();
    delete(vec[ix]);
  }

  vec.clear();
}
