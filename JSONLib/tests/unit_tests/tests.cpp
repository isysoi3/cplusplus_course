#include "gtest/gtest.h"
#include "JSON.cpp"

TEST(EmptyJSON, Equals) {
    JSON json;
    EXPECT_EQ(json.isEmpty(), true);
}