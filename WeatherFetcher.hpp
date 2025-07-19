// WeatherFetcher.hpp
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Declare the functions
std::string getWeatherData(const std::string& cityName, const std::string& apiKey);
std::string extract(const std::string& data, const std::string& key);
std::string loadApiKey(const std::string& filename);
