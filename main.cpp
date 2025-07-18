#include <iostream>
#include <string>
#include <curl/curl.h>

// Function that curl calls as it receives chunks of data
size_t StoreDownloadedData(void* downloadedData, size_t byteSizePerItem, size_t itemCount, std::string* outputString) {
    size_t totalBytes = byteSizePerItem * itemCount;
    outputString->append((char*)downloadedData, totalBytes);
    return totalBytes;
}

// Function that builds URL and makes HTTP request
std::string getWeatherData(const std::string& cityName, const std::string& apiKey) {
    CURL* curlHandle = curl_easy_init();
    std::string jsonResponse;

    if (curlHandle) {
        std::string apiUrl = "https://api.openweathermap.org/data/2.5/weather?q=" 
                           + cityName + "&appid=" + apiKey + "&units=metric";

        curl_easy_setopt(curlHandle, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, StoreDownloadedData);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &jsonResponse);

        CURLcode result = curl_easy_perform(curlHandle);

        if (result != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: "
                      << curl_easy_strerror(result) << std::endl;
        }

        curl_easy_cleanup(curlHandle);
        
    }

    return jsonResponse;
}

// Main program entry point
int main() {
    std::string cityName = "London,uk";
    std::string apiKey = "7f57de96d21a8624bae5c7c11b44ddfe";

    std::string json = getWeatherData(cityName, apiKey); 

    std::cout << "Raw weather response:\n" << json << std::endl;
    return 0;
}
