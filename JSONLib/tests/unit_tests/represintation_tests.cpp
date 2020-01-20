//
// Created by Ilya Sysoi on 1/19/20.
//

#include <Reader/ReaderException.h>
#include "gtest/gtest.h"
#include "JSON/JSON.h"
#include "Reader/Reader.h"

TEST(parsemptyJSONString, Equals) {
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

TEST(parseNullJSONString, Equals) {
    std::string expected = "{ \"1\" : null }";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseStringJSONString, Equals) {
    std::string expected = R"({ "1" : "test" })";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseArrayJSONString, Equals) {
    std::string expected = R"([1, 2])";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseComplexJSONString, Equals) {
    std::string expected = R"({ "1" : null,  "array" : [{ "1" : null }, { "1" : null }],  "json" : { "1" : 1 } })";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseComplex2JSONString, Equals) {
    std::string expected = "[1, 2, { \"a\" : [1, 2] }]";
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

TEST(parseInvlaidJSON, Equals) {
    std::string jsonString = "[1, 2, { \"a\": [1, 2] }";
    std::string expected = "Invalid json";

    try {
        Reader().parse(jsonString).toString();
    } catch (ReaderException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(parseBadStateJSON, Equals) {
    std::string jsonString = "[1, 2, { 1 : nil }";
    std::string expected = "Bad state";

    try {
        Reader().parse(jsonString).toString();
    } catch (ReaderException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(parseInvalidFormatJSON, Equals) {
    std::string jsonString = "{ 1 : 1}";
    std::string expected = "Invalid format";

    try {
        Reader().parse(jsonString).toString();
    } catch (ReaderException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(parseFailedJSON, Equals) {
    std::string jsonString = "[1, , { 1 : }";
    std::string expected = "Parsing failed";

    try {
        Reader().parse(jsonString).toString();
    } catch (ReaderException &ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(toString, Equals) {
    JSON root;
    std::string value = "test";
    std::string key = "1";
    root.addValue(key, value);

    std::string expected = R"({ "1" : "test" })";
    std::string actual = root.toString();
    EXPECT_EQ(expected, actual);
}

TEST(toStringComplex, Equals) {
    JSON root;
    std::string value = "test";
    std::string key = "1";
    root.addValue(key, value);

    auto array = Array();
    array.emplace_back(1);
    array.emplace_back(2);
    JSON child = JSON(array);
    root.addValue("array", child);

    std::string expected = R"({ "1" : "test",  "array" : [1, 2] })";
    std::string actual = root.toString();
    EXPECT_EQ(expected, actual);
}

TEST(inputAndOutputStreams, Equals) {
    std::string expected = "[1, 2]";
    std::stringstream ss;
    JSON json;
    ss << expected;
    ss >> json;
    std::string actual = Reader().parse(expected).toString();

    EXPECT_EQ(expected, actual);
}

