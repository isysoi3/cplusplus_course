#include "gtest/gtest.h"
#include "JSON/JSON.h"

TEST(isEmpty, Equals) {
    JSON json;
    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isNotEmpty, Equals) {
    JSON json = {1, 2};
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(initializerList, Equals) {
    JSON json = { 1, 1.3 };

    bool expected = true;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isJSON, Equals) {
    JSON::Array array = {212, 22, 22};
    JSON json = { {"12", 2}, { "2" , array}};

    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isJSONAndArray, Equals) {
    JSON childArray = { 212, 22, 22 };
    JSON json = { {"12", 2}, { "2" , childArray}};

    EXPECT_EQ(json.isArray(), false);
    EXPECT_EQ( (*json.getValue<JSON>("2")).isArray(), true);
}

TEST(isNotArray, Equals) {
    JSON json;
    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(copyJSON, Equals) {
    JSON json1 = JSON();
    JSON json2 = json1;

    EXPECT_EQ(json1, json2);
}

TEST(copyJSONAndEdit, NotEquals) {
    std::string key = "test";

    JSON json1 = JSON();
    json1.addValue(key, 1);
    JSON json2 = json1;
    json2.addValue(key, 2);

    EXPECT_NE(json1[key], json2[key]);
}