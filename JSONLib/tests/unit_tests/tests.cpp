#include "gtest/gtest.h"
#include "JSON.h"
#include "Reader.h"

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

    std::string expected = R"({ "1" : "test" })";
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

    std::string expected = R"({ "1" : "test",  "array" : [1, 2] })";
    std::string actual = root.toString();
    EXPECT_EQ(expected, actual);
}

TEST(parseEmptyJSONString, Equals) {
    std::string expected = "{}";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseBoolJSONString, Equals) {
    std::string expected = "{ \"1\" : true }";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseIntJSONString, Equals) {
    std::string expected = "{ \"1\" : 1 }";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseDoubleJSONString, Equals) {
    std::string expected = "{ \"1\" : 1.4 }";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parsNullJSONString, Equals) {
    std::string expected = "{ \"1\" : null }";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parsStringJSONString, Equals) {
    std::string expected = R"({ "1" : "test" })";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parsArrayJSONString, Equals) {
    std::string expected = R"([1, 2])";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parsComplexJSONString, Equals) {
    std::string expected = R"({ "1" : null,  "array" : [{ "1" : null }, { "1" : null }],  "json" : { "1" : 1 } })";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parsComplex2JSONString, Equals) {
    std::string expected = "[1, 2, { \"a\" : [1, 2] }]";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}




