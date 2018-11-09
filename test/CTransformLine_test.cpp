/*
 * CTransformLine_test.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: ominenko
 */
#ifdef TEST
#include "../CTransformLine.h"
#include "gtest/gtest.h"
#include <ArduinoJson.h>
#include <iostream>

class CTransformLineTest: public testing::Test {
public:
  CTransformLine TransformLine;
  void deserialize(const char *json) {
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, json);
    JsonObject root = doc.as<JsonObject>();
    TransformLine.deSerialize(root);
  }

  void serelize() {
    StaticJsonDocument<1024> doc;
    JsonObject root = doc.to<JsonObject>();
    TransformLine.serialize(root);
    serializeJson(doc,std::cout);
    std::cout<<std::endl;
  }

  void SetUp() override {
    deserialize("{offset:0,points:[ {20:0}, {40:50}, {10:-5}]}");
  }
};

TEST_F (CTransformLineTest, point) {
  EXPECT_EQ( TransformLine.convert(10),-5);
  EXPECT_EQ( TransformLine.convert(20),0);
  EXPECT_EQ( TransformLine.convert(40),50);
}

TEST_F (CTransformLineTest, in_range) {
  EXPECT_EQ( TransformLine.convert(15),-2.5);
  EXPECT_EQ( TransformLine.convert(30),25);
}

TEST_F (CTransformLineTest, less_range) {
  EXPECT_EQ( TransformLine.convert(0),-10);
}

TEST_F (CTransformLineTest, over_range) {
  EXPECT_EQ( TransformLine.convert(60),100);
}

TEST_F (CTransformLineTest, offset) {
  deserialize("{offset:1.5 ,points:[ {20:0}, {40:50}, {10:-5}]}");
  EXPECT_EQ( TransformLine.convert(10),-3.5);
  EXPECT_EQ( TransformLine.convert(15),-1);
  EXPECT_EQ( TransformLine.convert(0),-8.5);
  EXPECT_EQ( TransformLine.convert(60),101.5);
}
#endif
