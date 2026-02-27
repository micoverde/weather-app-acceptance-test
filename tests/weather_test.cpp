#include <gtest/gtest.h>
#include "weather_client.hpp"

class WeatherClientTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(WeatherClientTest, ParseValidTemperature) {
    std::string validJson = R"({
        "current_condition": [
            {
                "temp_F": "45",
                "temp_C": "7",
                "humidity": "80"
            }
        ]
    })";

    std::string temp = WeatherClient::parseTemperature(validJson);
    EXPECT_EQ(temp, "45");
}

TEST_F(WeatherClientTest, ParseNegativeTemperature) {
    std::string validJson = R"({
        "current_condition": [
            {
                "temp_F": "-10",
                "temp_C": "-23"
            }
        ]
    })";

    std::string temp = WeatherClient::parseTemperature(validJson);
    EXPECT_EQ(temp, "-10");
}

TEST_F(WeatherClientTest, ParseHighTemperature) {
    std::string validJson = R"({
        "current_condition": [
            {
                "temp_F": "105",
                "temp_C": "41"
            }
        ]
    })";

    std::string temp = WeatherClient::parseTemperature(validJson);
    EXPECT_EQ(temp, "105");
}

TEST_F(WeatherClientTest, ThrowsOnMissingCurrentCondition) {
    std::string invalidJson = R"({
        "weather": []
    })";

    EXPECT_THROW(WeatherClient::parseTemperature(invalidJson), std::runtime_error);
}

TEST_F(WeatherClientTest, ThrowsOnEmptyCurrentCondition) {
    std::string invalidJson = R"({
        "current_condition": []
    })";

    EXPECT_THROW(WeatherClient::parseTemperature(invalidJson), std::runtime_error);
}

TEST_F(WeatherClientTest, ThrowsOnMissingTempF) {
    std::string invalidJson = R"({
        "current_condition": [
            {
                "temp_C": "7"
            }
        ]
    })";

    EXPECT_THROW(WeatherClient::parseTemperature(invalidJson), std::runtime_error);
}

TEST_F(WeatherClientTest, ThrowsOnInvalidJson) {
    std::string invalidJson = "not a json";

    EXPECT_THROW(WeatherClient::parseTemperature(invalidJson), std::runtime_error);
}

TEST_F(WeatherClientTest, ThrowsOnEmptyJson) {
    std::string emptyJson = "";

    EXPECT_THROW(WeatherClient::parseTemperature(emptyJson), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
