
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

TEST(UriTest, CreateTarget) {
    Uri uri = Uri("/game/{gameId}");

    std::map<std::string, std::string> dynamicComponents;
    dynamicComponents["gameId"] = "someGameId";
    std::map<std::string, std::string> filters;
    filters["filter1"] = "value1";
    filters["filter2"] = "value2";

    auto target = uri.buildTarget(dynamicComponents, filters);

    EXPECT_EQ(*target, "/game/someGameId?filter1=value1&filter2=value2");
}
