
#include "Uri.h"
#include <gtest/gtest.h>

TEST(UriTest, ParseStaticSuccess) {
    Uri uri = Uri("/game", http::verb::get);

    EXPECT_TRUE(uri.canParse("/game", http::verb::get));
}

TEST(UriTest, ParseStaticFail) {
    Uri uri = Uri("/game", http::verb::get);

    EXPECT_FALSE(uri.canParse("/notGame", http::verb::get));
}

TEST(UriTest, ParseStaticFailBecauseVerb) {
    Uri uri = Uri("/game", http::verb::get);

    EXPECT_FALSE(uri.canParse("/game", http::verb::put));
}

TEST(UriTest, ParseDynamicSuccess) {
    Uri uri = Uri("/game/{gameId}", http::verb::get);

    EXPECT_TRUE(uri.canParse("/game/haha", http::verb::get));
}

TEST(UriTest, ParseDynamicWithFilters) {
    Uri uri = Uri("/game/{gameId}", http::verb::get);

    EXPECT_TRUE(uri.canParse("/game/haha?key=value", http::verb::get));
}

TEST(UriTest, ParseFilters) {
    Uri uri = Uri("/game/{gameId}", http::verb::get);

    auto filters = uri.parseFilters("/game/haha?key=value");

    EXPECT_EQ(filters->at("key"), "value");
}

TEST(UriTest, ParseDynamic) {
    Uri uri = Uri("/game/{gameId}", http::verb::get);

    auto dynamicComponents = uri.parseDynamicComponents("/game/haha?key=value");

    EXPECT_EQ(dynamicComponents->at("gameId"), "haha");
}
