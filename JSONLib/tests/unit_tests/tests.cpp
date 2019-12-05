#include "gtest/gtest.h"
#include "JSON.h"

TEST(EmptyJSON, Equals) {
    JSON json;
    EXPECT_EQ(json.isEmpty(), true);
}

TEST(NoEmptyJSON, Equals) {
    JSON json;
    json.addValue("1", 2);
    EXPECT_EQ(json.isEmpty(), false);
}

TEST(GetValue, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);
    auto rez = json.getValue<std::string>(key);
    EXPECT_EQ(rez->c_str(), value);
}

TEST(GetValueFromEmpty, Equals) {
    JSON json;
    std::string key = "1";
    EXPECT_EQ(json.getValue<int>(key), nullptr);
}

TEST(isArray, Equals) {
    auto array = JSON::Array();
    JSON json = JSON(array);
    EXPECT_EQ(json.isArray(), true);
}

TEST(isNotArray, NotEquals) {
    JSON json;
    EXPECT_EQ(json.isArray(), false);
}