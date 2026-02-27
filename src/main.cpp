#include "weather_client.hpp"
#include <iostream>

void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <location>" << std::endl;
    std::cerr << "Example: " << programName << " beijing" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string location = argv[1];

    try {
        WeatherClient client;
        std::string temperature = client.getTemperature(location);
        std::cout << "Temperature in " << location << ": " << temperature << "°F" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
