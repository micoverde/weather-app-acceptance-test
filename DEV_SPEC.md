# Weather App Development Specification

## Architecture

### Project Structure
```
playground/
├── FUNC_SPEC.md          # Functional specification
├── DEV_SPEC.md           # This file
├── CMakeLists.txt        # CMake build configuration
├── src/
│   ├── main.cpp          # Entry point
│   ├── weather_client.hpp # Weather API client header
│   └── weather_client.cpp # Weather API client implementation
└── tests/
    └── weather_test.cpp  # Unit tests
```

### Components

#### 1. WeatherClient Class
Responsible for HTTP communication and JSON parsing.

**Public Interface:**
```cpp
class WeatherClient {
public:
    WeatherClient();
    ~WeatherClient();

    // Fetches temperature for given location
    // Returns temperature in Fahrenheit as string
    // Throws std::runtime_error on failure
    std::string getTemperature(const std::string& location);

    // For testing: parse JSON response
    static std::string parseTemperature(const std::string& jsonResponse);
};
```

**Private Members:**
- CURL handle management
- HTTP response callback

#### 2. Main Function
- Parse command-line arguments
- Create WeatherClient instance
- Call getTemperature()
- Output result or error

## Dependencies

### External Libraries
| Library | Purpose | Ubuntu Package |
|---------|---------|----------------|
| libcurl | HTTP requests | libcurl4-openssl-dev |
| nlohmann-json | JSON parsing | nlohmann-json3-dev |
| Google Test | Unit testing | libgtest-dev |

### Build Tools
- CMake (>= 3.14)
- g++ (C++17 support)

## Build Instructions

```bash
# Install dependencies
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev libgtest-dev cmake g++

# Build
mkdir -p build && cd build
cmake ..
make

# Run tests
./weather_test

# Run application
./weather_app beijing
```

## API Details

### wttr.in JSON Response Structure
```json
{
  "current_condition": [
    {
      "temp_F": "45",
      "temp_C": "7",
      ...
    }
  ],
  ...
}
```

### Error Scenarios
1. **Network failure**: CURL returns non-CURLE_OK
2. **Invalid location**: API returns error or empty data
3. **JSON parse error**: Response is not valid JSON

## Testing Strategy

### Unit Tests
1. **JSON Parsing**: Test parseTemperature() with sample JSON
2. **Error Handling**: Test with malformed JSON
3. **Empty Response**: Test with empty data

### Integration Tests
1. **Live API call**: Test with known location (may be skipped in CI)

## Code Standards
- C++17 standard
- Use smart pointers where appropriate
- RAII for resource management (CURL handles)
- Clear error messages for user-facing errors
