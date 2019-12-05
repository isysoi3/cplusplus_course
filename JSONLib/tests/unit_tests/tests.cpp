#include "gtest/gtest.h"
#include "JSON.h"

TEST(EmptyJSON, Equals) {
    JSON json;
    EXPECT_EQ(json.isEmpty(), true);
}

TEST(AddValue, Equals) {
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

TEST(JSONConstr, Equals) {
    JSON json1;
    JSON json2 = JSON(json1);
    EXPECT_EQ(json1.isArray(), json1.isArray());
}

TEST(ToString, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);
    std::string value_string = json.toString();
    printf("%s", value_string.c_str());
    EXPECT_EQ(value_string, "{}");
}