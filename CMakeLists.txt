cmake_minimum_required(VERSION 3.14)
project(weather_app VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# Weather client library
add_library(weather_client
    src/weather_client.cpp
)

target_include_directories(weather_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(weather_client
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

# Main executable
add_executable(weather_app
    src/main.cpp
)

target_link_libraries(weather_app
    weather_client
)

# Testing
enable_testing()
find_package(GTest REQUIRED)

add_executable(weather_test
    tests/weather_test.cpp
)

target_link_libraries(weather_test
    weather_client
    GTest::GTest
    GTest::Main
)

add_test(NAME WeatherTest COMMAND weather_test)
