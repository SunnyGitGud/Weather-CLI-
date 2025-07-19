// WeatherFetcher.cpp
#include "weatherFrame.hpp"
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <iostream>

std::string loadApiKey(const std::string& filename) {
    std::ifstream file(filename);
    std::string key;
    if (file.is_open()) {
        std::getline(file, key);
        file.close();
    } else {
        std::cerr << "ERROR: Could not open API key file: " << filename << std::endl;
    }
    return key;
}



size_t StoreDownloadedData(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string getWeatherData(const std::string& cityName, const std::string& apiKey) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" +
                          cityName + "&appid=" + apiKey + "&units=metric";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, StoreDownloadedData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

std::string extract(const std::string& data, const std::string& key) {
    size_t keyPos = data.find(key);
    if (keyPos == std::string::npos) return "Not Found";

    size_t colon = data.find(":", keyPos);
    size_t start = data.find_first_of("0123456789-", colon);
    size_t end = data.find_first_not_of("0123456789.-", start);

    return data.substr(start, end - start);
}

