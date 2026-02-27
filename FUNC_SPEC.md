# Weather App Functional Specification

## Overview
A command-line application that retrieves and displays the current temperature for a given location.

## Features

### Core Functionality
- Accept a place name as a command-line argument
- Query the wttr.in weather API for current weather data
- Display the temperature in Fahrenheit

### Input
- **CLI Argument**: A place name (e.g., "beijing", "london", "new+york")
- Place names with spaces should be URL-encoded or use `+` as separator

### Output
- Current temperature in Fahrenheit for the specified location
- Format: `Temperature in <location>: <temp>°F`

### Error Handling
- Display usage information if no location is provided
- Display error message if the API request fails
- Display error message if the location is not found

## API Integration

### wttr.in API
- **Endpoint**: `https://wttr.in/<location>?format=j1`
- **Method**: GET
- **Authentication**: None required
- **Response Format**: JSON

### Response Data Used
- `current_condition[0].temp_F`: Current temperature in Fahrenheit

## Example Usage

```bash
# Get temperature for Beijing
./weather_app beijing
# Output: Temperature in beijing: 45°F

# Get temperature for New York
./weather_app new+york
# Output: Temperature in new+york: 38°F
```

## Non-Functional Requirements
- Response time: Should complete within 10 seconds (network dependent)
- Cross-platform: Linux support required
- Dependencies: libcurl for HTTP requests, nlohmann-json for JSON parsing
