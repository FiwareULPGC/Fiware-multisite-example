#ifndef SRC_LIB_NGSI_METADATA_H_
#define SRC_LIB_NGSI_METADATA_H_

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
#include "ngsi/Request.h"
#include "ngsi/Association.h"

/* Metadata interpreted by Orion Context Broker, i.e. not custom metadata */
#define NGSI_MD_ID       "ID"
#define NGSI_MD_LOCATION "location"
#define NGSI_MD_CREDATE  "creDate"    // FIXME P5: to be used for creDate (currenly only in DB)
#define NGSI_MD_MODDATE  "modDate"    // FIXME P5: to be used for modDate (currenly only in DB)



/* ****************************************************************************
*
* Metadata -
*
* FIXME
*   The Association field should be added not in this class but in a class that inherits
*   from Metadata.
*    Once we start the next refactoring ...
*/
typedef struct Metadata
{
  std::string  name;         // Mandatory
  std::string  type;         // Optional
  std::string  value;        // Mandatory
  Association  association;  // Optional (used if type == 'Association')

  Metadata();
  Metadata(Metadata* mP);
  Metadata(const std::string& _name, const std::string& _type, const std::string& _value = "");

  std::string  render(Format format, const std::string& indent, bool comma = false);
  std::string  toJson(bool isLastElement);
  void         present(const std::string& metadataType, int ix, const std::string& indent);
  void         release(void);
  void         fill(const struct Metadata& md);

  std::string  check(RequestType         requestType,
                     Format              format,
                     const std::string&  indent,
                     const std::string&  predetectedError,
                     int                 counter);
} Metadata;

#endif  // SRC_LIB_NGSI_METADATA_H_
