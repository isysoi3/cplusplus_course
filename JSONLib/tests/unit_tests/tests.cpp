#include "gtest/gtest.h"
#include "JSON.h"

TEST(EmptyJSON, Equals) {
    JSON json;
    EXPECT_EQ(json.isEmpty(), true);
}

//TEST(NoEmptyJSON, Equals) {
//    JSON json;
//    json.addValue("1", 2);
//    EXPECT_EQ(json.isEmpty(), false);
//}
//
//TEST(GetValue, Equals) {
//    JSON json;
//    std::string value = "test";
//    std::string key = "1";
//    json.addValue(key, value);
//    EXPECT_EQ(json.getValue(key), value);
//}
//
//TEST(GetEmptyValue, Equals) {
//    JSON json;
//    std::string key = "1";
//    EXPECT_EQ(json.getValue(key), nullptr);
//}