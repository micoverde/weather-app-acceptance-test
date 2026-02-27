#ifndef WEATHER_CLIENT_HPP
#define WEATHER_CLIENT_HPP

#include <string>

class WeatherClient {
public:
    WeatherClient();
    ~WeatherClient();

    // Fetches temperature for given location
    // Returns temperature in Fahrenheit as string
    // Throws std::runtime_error on failure
    std::string getTemperature(const std::string& location);

    // For testing: parse JSON response to extract temperature
    static std::string parseTemperature(const std::string& jsonResponse);

private:
    // Performs HTTP GET request and returns response body
    std::string httpGet(const std::string& url);

    // Callback function for CURL to write response data
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif // WEATHER_CLIENT_HPP
