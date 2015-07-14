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

#include "testDataFromFile.h"
#include "common/globals.h"
#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "xmlParse/xmlRequest.h"
#include "xmlParse/xmlParse.h"
#include "jsonParse/jsonRequest.h"

#include "unittest.h"



/* ****************************************************************************
*
* badSubscriptionId_xml - 
*/
TEST(UnsubscribeContextRequest, badSubscriptionId_xml)
{
  ParseData       reqData;
  ConnectionInfo  ci("", "POST", "1.1");
  const char*     infile   = "ngsi10.unsubscribeContextRequest.subscriptionId.invalid.xml";
  const char*     outfile1 = "ngsi10.unsubscribeContextResponse.invalidSubscriptionId.valid.xml";
  const char*     outfile2 = "ngsi10.unsubscribeContextResponse.invalidSubscriptionId2.valid.xml";
  std::string     out;

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";

  lmTraceLevelSet(LmtDump, true);
  out = xmlTreat(testBuf, &ci, &reqData, UnsubscribeContext, "unsubscribeContextRequest", NULL);
  lmTraceLevelSet(LmtDump, false);

  EXPECT_STREQ(expectedBuf, out.c_str());

  //
  // With the data obtained, render, present and release methods are exercised
  //
  UnsubscribeContextRequest*  ucrP = &reqData.uncr.res;
  
  ucrP->present(""); // No output

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";

  out = ucrP->render(UnsubscribeContext, XML, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  ucrP->release();
}



/* ****************************************************************************
*
* badSubscriptionId_json - 
*/
TEST(UnsubscribeContextRequest, badSubscriptionId_json)
{
  ParseData       reqData;
  ConnectionInfo  ci("", "POST", "1.1");
  const char*     infile   = "ngsi10.unsubscribeContextRequest.badSubscriptionId.invalid.json";
  std::string     out;
  const char*     outfile2 = "ngsi10.unsubscribeContextResponse.badSubscriptionId2.valid.json";

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";
  
  ci.inFormat  = JSON;
  ci.outFormat = JSON;
  lmTraceLevelSet(LmtDump, true);
  out = jsonTreat(testBuf, &ci, &reqData, UnsubscribeContext, "unsubscribeContextRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_STREQ("OK", out.c_str());
  
  UnsubscribeContextRequest*  ucrP = &reqData.uncr.res;

  ucrP->present("");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  out = ucrP->render(UnsubscribeContext, JSON, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  ucrP->release();
}
