#ifndef SRC_LIB_NGSI_SCOPE_H_
#define SRC_LIB_NGSI_SCOPE_H_

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

#include "ngsi/Request.h"
#include "common/Format.h"
#include "orionTypes/areas.h"

using namespace orion;



/* ****************************************************************************
*
* Defined scopes so far
*/
#define SCOPE_TYPE_ASSOC           "IncludeAssociations"
#define SCOPE_VALUE_ASSOC_SOURCE   "SOURCES"
#define SCOPE_VALUE_ASSOC_TARGET   "TARGETS"
#define SCOPE_VALUE_ASSOC_ALL      "ALL"

#define SCOPE_OPERATOR_NOT           "Not"

#define SCOPE_FILTER                 "FIWARE" "::" "Filter"
#define SCOPE_FILTER_EXISTENCE       SCOPE_FILTER "::" "Existence"
#define SCOPE_FILTER_NOT_EXISTENCE   SCOPE_FILTER "::" SCOPE_OPERATOR_NOT "::" "Existence"

#define SCOPE_VALUE_ENTITY_TYPE      "entity::type"



/* ****************************************************************************
*
* Scope -
*/
typedef struct Scope
{
  std::string  type;     // Mandatory
  std::string  value;    // Mandatory

  std::string  oper;     // Optional - used for filters

  orion::AreaType     areaType;
  orion::Circle       circle;
  orion::Polygon      polygon;

  Scope();
  Scope(const std::string& _type, const std::string& _value);

  std::string render(Format format, const std::string& indent, bool notLastInVector);
  void        present(const std::string& indent, int ix);
  void        release(void);

  std::string check(RequestType         requestType,
                    Format              format,
                    const std::string&  indent,
                    const std::string&  predetectedError,
                    int                 counter);
} Scope;

#endif  // SRC_LIB_NGSI_SCOPE_H_
