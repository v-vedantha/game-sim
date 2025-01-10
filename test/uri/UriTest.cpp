
#include "Uri.h"
#include <gtest/gtest.h>

TEST(UriTest, ParseStaticSuccess) {
    Uri uri = Uri("/game");

    EXPECT_TRUE(uri.canParse("/game"));
}

TEST(UriTest, ParseStaticFail) {
    Uri uri = Uri("/game");

    EXPECT_FALSE(uri.canParse("/notGame"));
}

TEST(UriTest, ParseDynamicSuccess) {
    Uri uri = Uri("/game/{gameId}");

    EXPECT_TRUE(uri.canParse("/game/haha"));
}

TEST(UriTest, ParseDynamicWithFilters) {
    Uri uri = Uri("/game/{gameId}");

    EXPECT_TRUE(uri.canParse("/game/haha?key=value"));
}

TEST(UriTest, ParseFilters) {
    Uri uri = Uri("/game/{gameId}");

    auto filters = uri.parseFilters("/game/haha?key=value");

    EXPECT_EQ(filters->at("key"), "value");
}

TEST(UriTest, ParseDynamic) {
    Uri uri = Uri("/game/{gameId}");

    auto dynamicComponents = uri.parseDynamicComponents("/game/haha?key=value");

    EXPECT_EQ(dynamicComponents->at("gameId"), "haha");
}
