//
// Created by Ilya Sysoi on 1/19/20.
//

#include "gtest/gtest.h"
#include "JSON/JSON.h"

TEST(getInt, Equals) {
    JSON json;
    int value = 1;
    std::string key = "1";
    json.addValue(key, value);

    int expected = value;
    auto actual = json.getValue<int>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getBool, Equals) {
    JSON json;
    bool value = true;
    std::string key = "1";
    json.addValue(key, value);

    bool expected = value;
    auto actual = json.getValue<bool>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getString, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);

    std::string expected = value;
    auto actual = json.getValue<std::string>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getJSON, Equals) {
    JSON json;
    JSON value = JSON({1, 2});;
    std::string key = "1";
    json.addValue(key, value);

    JSON expected = value;
    auto actual = json.getValue<JSON>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getNull, Equals) {
    JSON json;
    void *value = nullptr;
    std::string key = "1";
    json.addValue(key, value);

    void *expected = value;
    auto actual = json.getValue<void *>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getArray, Equals) {
    JSON::Array array = {1, 2};
    JSON json = JSON(array);

    JSON::Array expected = array;
    auto actual = json.asArray();
    EXPECT_EQ(expected, actual);
}

TEST(getNonExists, Equals) {
    JSON json;
    std::string key = "1";
    auto expected = std::nullopt;
    auto actual = json.getValue<int>(key);
    EXPECT_EQ(expected, actual);
}