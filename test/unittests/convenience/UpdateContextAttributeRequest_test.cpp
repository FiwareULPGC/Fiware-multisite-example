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
#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/Format.h"
#include "convenience/UpdateContextAttributeRequest.h"
#include "convenience/ContextAttributeResponseVector.h"

#include "unittest.h"



/* ****************************************************************************
*
* render_xml - 
*/
TEST(UpdateContextAttributeRequest, render_xml)
{
  UpdateContextAttributeRequest  ucar;
  Metadata                       mdata("name", "type", "value");
  std::string                    out;
  const char*                    outfile = "ngsi10.updateContextAttributeRequest.render.valid.xml";

  utInit();

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";

  ucar.type         = "TYPE";
  ucar.contextValue = "Context Value";

  ucar.metadataVector.push_back(&mdata);
  out = ucar.render(XML, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}



/* ****************************************************************************
*
* render_json - 
*/
TEST(UpdateContextAttributeRequest, render_json)
{
  UpdateContextAttributeRequest  ucar;
  Metadata                       mdata("name", "type", "value");
  std::string                    out;
  const char*                    outfile = "ngsi10.updateContextAttributeRequest.render.valid.json";

  utInit();

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";

  ucar.type         = "TYPE";
  ucar.contextValue = "Context Value";

  ucar.metadataVector.push_back(&mdata);
  out = ucar.render(JSON, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}



/* ****************************************************************************
*
* check_xml - 
*/
TEST(UpdateContextAttributeRequest, check_xml)
{
  UpdateContextAttributeRequest  ucar;
  Metadata                       mdata("name", "type", "value");
  Metadata                       mdata2("", "type", "value");
  std::string                    out;
  const char*                    outfile1 = "ngsi10.updateContextAttributeRequest.check1.valid.xml";
  const char*                    outfile2 = "ngsi10.updateContextAttributeRequest.check2.valid.xml";
  const char*                    outfile3 = "ngsi10.updateContextAttributeRequest.check3.valid.xml";

  utInit();

  ucar.metadataVector.push_back(&mdata);

  // 1. predetectedError + Format ZERO => XML
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";
  out = ucar.check(UpdateContextAttribute, (Format) 0, "", "PRE Error", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  
  // 2. empty contextValue
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  out = ucar.check(UpdateContextAttribute, XML, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  // 3. OK
  ucar.contextValue = "CValue";
  out = ucar.check(UpdateContextAttribute, XML, "", "", 0);
  EXPECT_STREQ("OK", out.c_str());

  // 4. bad metadata
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile3)) << "Error getting test data from '" << outfile3 << "'";
  ucar.metadataVector.push_back(&mdata2);
  out = ucar.check(UpdateContextAttribute, XML, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}



/* ****************************************************************************
*
* check_json - 
*/
TEST(UpdateContextAttributeRequest, check_json)
{
  UpdateContextAttributeRequest  ucar;
  Metadata                       mdata("name", "type", "value");
  Metadata                       mdata2("", "type", "value");
  std::string                    out;
  const char*                    outfile1 = "ngsi10.updateContextAttributeRequest.check1.valid.json";
  const char*                    outfile2 = "ngsi10.updateContextAttributeRequest.check2.valid.json";
  const char*                    outfile3 = "ngsi10.updateContextAttributeRequest.check3.valid.json";

  utInit();

  ucar.metadataVector.push_back(&mdata);

  // 1. predetectedError
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";
  out = ucar.check(UpdateContextAttribute, JSON, "", "PRE Error", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  
  // 2. empty contextValue
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  out = ucar.check(UpdateContextAttribute, JSON, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  // 3. OK
  ucar.contextValue = "CValue";
  out = ucar.check(UpdateContextAttribute, JSON, "", "", 0);
  EXPECT_STREQ("OK", out.c_str());

  // 4. bad metadata
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile3)) << "Error getting test data from '" << outfile3 << "'";
  ucar.metadataVector.push_back(&mdata2);
  out = ucar.check(UpdateContextAttribute, JSON, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}



/* ****************************************************************************
*
* present - just exercise the code
*/
TEST(UpdateContextAttributeRequest, present)
{
  UpdateContextAttributeRequest  ucar;
  Metadata                       mdata("name", "type", "value");

  ucar.metadataVector.push_back(&mdata);

  ucar.present("");
}



/* ****************************************************************************
*
* release - 
*/
TEST(UpdateContextAttributeRequest, release)
{
  UpdateContextAttributeRequest  ucar;
  Metadata*                      mdataP = new Metadata("name", "type", "value");

  ucar.metadataVector.push_back(mdataP);
  ASSERT_EQ(1, ucar.metadataVector.size());
  ucar.release();
  EXPECT_EQ(0, ucar.metadataVector.size());
}
