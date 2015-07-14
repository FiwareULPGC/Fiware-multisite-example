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
* Author: Fermin Galan
*/
#include <string>

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi10/NotifyContextRequest.h"
#include "ngsi10/NotifyContextResponse.h"
#include "rest/ConnectionInfo.h"



/* ****************************************************************************
*
* NotifyContextRequest::render -
*/
std::string NotifyContextRequest::render(ConnectionInfo* ciP, RequestType requestType, const std::string& indent)
{
  std::string  out                                  = "";
  std::string  tag                                  = "notifyContextRequest";
  bool         contextElementResponseVectorRendered = contextElementResponseVector.size() != 0;

  //
  // Note on JSON commas:
  //   subscriptionId and originator are MANDATORY.
  //   The only doubt here if whether originator should end in a comma.
  //   This doubt is taken care of by the variable 'contextElementResponseVectorRendered'
  //
  out += startTag(indent, tag, ciP->outFormat, false);
  out += subscriptionId.render(NotifyContext, ciP->outFormat, indent + "  ", true);
  out += originator.render(ciP->outFormat, indent  + "  ", contextElementResponseVectorRendered);
  out += contextElementResponseVector.render(ciP, NotifyContext, indent  + "  ", false);
  out += endTag(indent, tag, ciP->outFormat);

  return out;
}



/* ****************************************************************************
*
* NotifyContextRequest::check
*/
std::string NotifyContextRequest::check(ConnectionInfo* ciP, RequestType requestType, const std::string& indent, const std::string& predetectedError, int counter)
{
  std::string            res;
  NotifyContextResponse  response;
   
  if (predetectedError != "")
  {
    response.responseCode.fill(SccBadRequest, predetectedError);
  }
  else if (((res = subscriptionId.check(QueryContext, ciP->outFormat, indent, predetectedError, 0))               != "OK") ||
           ((res = originator.check(QueryContext, ciP->outFormat, indent, predetectedError, 0))                   != "OK") ||
           ((res = contextElementResponseVector.check(QueryContext, ciP->outFormat, indent, predetectedError, 0)) != "OK"))
  {
    response.responseCode.fill(SccBadRequest, res);
  }
  else
  {
    return "OK";
  }

  return response.render(NotifyContext, ciP->outFormat, indent);
}



/* ****************************************************************************
*
* NotifyContextRequest::present -
*/
void NotifyContextRequest::present(const std::string& indent)
{
  subscriptionId.present(indent);
  originator.present(indent);
  contextElementResponseVector.present(indent);
}



/* ****************************************************************************
*
* NotifyContextRequest::release -
*/
void NotifyContextRequest::release(void)
{
  contextElementResponseVector.release();
}
