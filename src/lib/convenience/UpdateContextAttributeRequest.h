#ifndef SRC_LIB_CONVENIENCE_UPDATECONTEXTATTRIBUTEREQUEST_H_
#define SRC_LIB_CONVENIENCE_UPDATECONTEXTATTRIBUTEREQUEST_H_

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

#include "common/Format.h"
#include "ngsi/MetadataVector.h"
#include "parse/CompoundValueNode.h"



/* ****************************************************************************
*
* UpdateContextAttributeRequest - 
*/
typedef struct UpdateContextAttributeRequest
{
  std::string                type;                // Optional
  std::string                contextValue;        // Mandatory
  MetadataVector             metadataVector;      // Optional

  std::string                typeFromXmlAttribute;
  orion::CompoundValueNode*  compoundValueP;

  UpdateContextAttributeRequest();
  std::string  render(Format format, std::string indent);
  std::string  check(RequestType requestType, Format format, std::string indent, std::string preError, int counter);
  void         present(std::string indent);
  void         release();
} UpdateContextAttributeRequest;

#endif  // SRC_LIB_CONVENIENCE_UPDATECONTEXTATTRIBUTEREQUEST_H_
