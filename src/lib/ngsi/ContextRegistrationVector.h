#ifndef SRC_LIB_NGSI_CONTEXTREGISTRATIONVECTOR_H_
#define SRC_LIB_NGSI_CONTEXTREGISTRATIONVECTOR_H_

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

#include "ngsi/ContextRegistration.h"



/* ****************************************************************************
*
* ContextRegistrationVector -
*/
typedef struct ContextRegistrationVector
{
  std::vector<ContextRegistration*>  vec;

  void                  push_back(ContextRegistration* item);
  unsigned int          size(void);
  ContextRegistration*  get(int ix);
  std::string           render(Format format, const std::string& indent, bool comma);
  void                  present(const std::string& indent);
  void                  release(void);

  std::string           check(RequestType         requestType,
                              Format              format,
                              const std::string&  indent,
                              const std::string&  predetectedError,
                              int                 counter);

  ContextRegistration*  operator[](unsigned int ix)
  {
    if (ix < vec.size())
    {
      return vec[ix];
    }

    return NULL;
  }

} ContextRegistrationVector;

#endif  // SRC_LIB_NGSI_CONTEXTREGISTRATIONVECTOR_H_