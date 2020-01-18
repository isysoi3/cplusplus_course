#include "gtest/gtest.h"
#include "JSON.h"

TEST(EmptyJSON, Equals) {
    JSON json;
    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(AddValue, Equals) {
    JSON json;
    json.addValue("1", 2);
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(GetValue, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);

    std::string expected = value;
    auto actual = json.getValue<std::string>(key);

    EXPECT_EQ(expected, actual->c_str());
}

TEST(GetValueFromEmpty, Equals) {
    JSON json;
    std::string key = "1";
    int* expected = nullptr;
    int* actual = json.getValue<int>(key);
    EXPECT_EQ(expected, actual);
}

TEST(isArray, Equals) {
    auto array = JSON::Array();
    JSON json = JSON(array);
    bool expected = true;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isNotArray, NotEquals) {
    JSON json;
    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(JSONConstr, Equals) {
    JSON json1;
    JSON json2 = JSON(json1);
    EXPECT_EQ(json1.isArray(), json1.isArray());
}

TEST(ToString, Equals) {
    JSON root;
    std::string value = "test";
    std::string key = "1";
    root.addValue(key, value);

    std::string expected = "{\n\t1 : test\n}";
    std::string actual = root.toString();
    EXPECT_EQ(expected, actual);
}

TEST(ToStringComplex, Equals) {
    JSON root;
    std::string value = "test";
    std::string key = "1";
    root.addValue(key, value);

    auto array = JSON::Array();
    array.emplace_back(1);
    array.emplace_back(2);
    JSON child = JSON(array);
    root.addValue("array", child);

    std::string expected = "{\n\t1 : test\n}";
    std::string actual = root.toString();
    EXPECT_EQ(expected, actual);
}

