//
// Created by Ilya Sysoi on 1/19/20.
//

#include <JSON/JSONException.h>
#include "gtest/gtest.h"
#include "JSON/JSON.h"

TEST(editInt, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, 2);
    JSON json2 = json1;
    json2.editValue(key, 102);

    EXPECT_NE(json1, json2);
}

TEST(editBool, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, true);
    JSON json2 = json1;
    json2.editValue(key, false);

    EXPECT_NE(json1, json2);
}

TEST(editString, NotEquals) {
    std::string key = "1";
    std::string value = "test";
    std::string newValue = "t";
    JSON json1;
    json1.addValue(key, value);
    JSON json2 = json1;
    json2.editValue(key, newValue);

    EXPECT_NE(json1, json2);
}

TEST(editToAnotherTypeKeyValue, NotEquals) {
    std::string key = "1";
    std::string value = "test";
    int newValue = 1;
    JSON json1;
    json1.addValue(key, value);
    JSON json2 = json1;
    json2.editValue(key, newValue);

    EXPECT_NE(json1, json2);
}

TEST(editJSON, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, JSON({1, 2}));
    JSON json2 = json1;
    json2.editValue(key, JSON({2}));

    EXPECT_NE(json1, json2);
}

TEST(editArray, NotEquals) {
    JSON json1 = JSON({1, 2});
    JSON json2 = json1;
    json2.editValue(0, 1.53);

    EXPECT_NE(json1, json2);
}

TEST(editKeyValueToArray, Equals) {
    std::string expected = "Failed to edit KeyValue in Array";
    JSON json = JSON({1, 2});
    try {
        json.editValue("123", "1");
    } catch (JSONException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayValueToArray, Equals) {
    std::string expected = "Failed to edit value in KeyValue";
    JSON json = JSON();
    try {
        json.editValue(1, "1");
    } catch (JSONException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayWithInvalidInxed, Equals) {
    std::string expected = "Invalid index";
    JSON json = JSON({1, 2});
    try {
        json.editValue(4, "1");
    } catch (JSONException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editNonExistingValue, Equals) {
    std::string expected = "No value for key";
    JSON json = JSON();
    try {
        json.editValue("1", "1");
    } catch (JSONException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}