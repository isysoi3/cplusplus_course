#include <Reader/ReaderException.h>
#include "gtest/gtest.h"
#include "JSON/JSON.h"
#include "Reader/Reader.h"

TEST(isEmpty, Equals) {
    JSON json;
    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isNotEmpty, Equals) {
    JSON json = JSON({1, 2});
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isArray, Equals) {
    JSON json = JSON({1, 2});
    bool expected = true;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isNotArray, Equals) {
    JSON json;
    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(addValue, Equals) {
    JSON json;
    json.addValue("1", 2);
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(editValue, Equals) {
    JSON json;
    json.addValue("1", 2);
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(getValue, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);

    std::string expected = value;
    auto actual = json.getValue<std::string>(key);

    EXPECT_EQ(expected, actual->c_str());
}

TEST(getValueFromEmpty, Equals) {
    JSON json;
    std::string key = "1";
    int *expected = nullptr;
    int *actual = json.getValue<int>(key);
    EXPECT_EQ(expected, actual);
}

TEST(copyJSON, Equals) {
    JSON json1;
    JSON json2 = JSON(json1);
    EXPECT_EQ(json1.isArray(), json1.isArray());
}