/*
 * presets_test.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#include "../CPresets.h"
#include "gtest/gtest.h"


class presetsTest : public testing::Test {

};

TEST_F (presetsTest, deserialize) {
	CPresets pr;
	pr.addFromJSON("{\"isActive\":false,\"data\":{\"type\":\"WeekDay\",\"weekDay\":{\"Value\":[false,false,false,false,false,false,false]},\"hours\":{\"Value\":[false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false]}}}");

	EXPECT_EQ(pr.items.size(), 1);

	EXPECT_EQ(((CPIIsActive*)pr.items.back())->isIsActive(), false);


	pr.addFromJSON("{\"isActive\":true,\"data\":{\"type\":\"WeekDay\",\"weekDay\":{\"Value\":[false,false,false,false,false,false,false]},\"hours\":{\"Value\":[false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false]}}}");

	EXPECT_EQ(pr.items.size(), 2);
	EXPECT_EQ(((CPIIsActive*)pr.items.back())->isIsActive(), true);
}

