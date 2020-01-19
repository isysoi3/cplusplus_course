//
// Created by Ilya Sysoi on 1/19/20.
//

#include "gtest/gtest.h"
#include "JSON/JSON.h"

TEST(addInt, Equals) {
    JSON json;
    json.addValue("1", 2);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addBool, Equals) {
    JSON json;
    json.addValue("1", true);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addString, Equals) {
    JSON json;
    json.addValue("1", "213123");

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addJSON, Equals) {
    JSON json;
    JSON child = JSON({1, 2});
    json.addValue("1", child);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addNull, Equals) {
    JSON json;
    json.addValue("1", nullptr);
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addArray, Equals) {
    JSON json = JSON({1, 2});
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}