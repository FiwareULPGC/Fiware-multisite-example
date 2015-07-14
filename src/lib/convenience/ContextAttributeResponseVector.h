#ifndef SRC_LIB_CONVENIENCE_CONTEXTATTRIBUTERESPONSEVECTOR_H_
#define SRC_LIB_CONVENIENCE_CONTEXTATTRIBUTERESPONSEVECTOR_H_

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

#include "convenience/ContextAttributeResponse.h"
#include "rest/ConnectionInfo.h"



/* ****************************************************************************
*
* ContextAttributeResponseVector - 
*/
typedef struct ContextAttributeResponseVector
{
  std::vector<ContextAttributeResponse*>  vec;

  std::string                render(ConnectionInfo* ciP, RequestType requestType, std::string indent);
  void                       present(std::string indent);
  void                       push_back(ContextAttributeResponse* item);
  unsigned int               size(void);
  ContextAttributeResponse*  get(int ix);
  void                       release(void);
  std::string                check(ConnectionInfo*  ciP,
                                   RequestType      requestType,
                                   std::string      indent,
                                   std::string      predetectedError,
                                   int              counter);
  void                       fill(ContextAttributeVector* cavP, const StatusCode& statusCode);

  ContextAttributeResponse*  operator[](unsigned int ix)
  {
    if (ix < vec.size())
    {
      return vec[ix];
    }

    return NULL;
  }
} ContextAttributeResponseVector;

#endif  // SRC_LIB_CONVENIENCE_CONTEXTATTRIBUTERESPONSEVECTOR_H_
