#include "weather_client.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

WeatherClient::WeatherClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

WeatherClient::~WeatherClient() {
    curl_global_cleanup();
}

size_t WeatherClient::writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string WeatherClient::httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "weather-app/1.0");

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error(std::string("HTTP request failed: ") + curl_easy_strerror(res));
    }

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode != 200) {
        throw std::runtime_error("HTTP error: " + std::to_string(httpCode));
    }

    return response;
}

std::string WeatherClient::parseTemperature(const std::string& jsonResponse) {
    try {
        json data = json::parse(jsonResponse);

        if (!data.contains("current_condition") ||
            !data["current_condition"].is_array() ||
            data["current_condition"].empty()) {
            throw std::runtime_error("Invalid response: missing current_condition");
        }

        const auto& current = data["current_condition"][0];

        if (!current.contains("temp_F")) {
            throw std::runtime_error("Invalid response: missing temp_F");
        }

        return current["temp_F"].get<std::string>();
    } catch (const json::exception& e) {
        throw std::runtime_error(std::string("JSON parsing error: ") + e.what());
    }
}

std::string WeatherClient::getTemperature(const std::string& location) {
    if (location.empty()) {
        throw std::runtime_error("Location cannot be empty");
    }

    std::string url = "https://wttr.in/" + location + "?format=j1";
    std::string response = httpGet(url);
    return parseTemperature(response);
}
