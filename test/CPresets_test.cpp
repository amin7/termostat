/*
 * presets_test.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */
//#ifdef TEST
#if 1
#include "../CPresets.h"
#include "gtest/gtest.h"


class presetsTest : public testing::Test {
public:
  CPresets presets_;
  void deserialize(const char *json) {
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, json);
    JsonObject root = doc.as<JsonObject>();
    presets_.deSerialize(root);
  }
};
const char *preset_v1 = "{\
  'Presets': [{\
      'weekDay': 1,\
      'hours': 2\
    },{\
      'weekDay': 3,\
      'hours': 1\
    }]\
}";

TEST_F (presetsTest, deserialize) {
  deserialize(preset_v1);
  EXPECT_EQ(presets_.items.size(), 2);

}

TEST_F (presetsTest, weekDay) {
  deserialize(preset_v1);
  auto day=presets_.find(0);
  EXPECT_FALSE(day==NULL);
  day=presets_.find(1);
  EXPECT_FALSE(day==NULL);
  day=presets_.find(2);
  EXPECT_TRUE(day==NULL);
}

TEST_F (presetsTest, hours) {
  deserialize(preset_v1);
  auto day=presets_.find(0);
  EXPECT_FALSE(day==NULL);
  EXPECT_FALSE(day->isInHome(0));
  EXPECT_TRUE(day->isInHome(1));
  EXPECT_FALSE(day->isInHome(23));

  day=presets_.find(1);
  EXPECT_FALSE(day==NULL);
  EXPECT_TRUE(day->isInHome(0));
  EXPECT_FALSE(day->isInHome(23));
}

#endif
