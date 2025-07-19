cmake_minimum_required(VERSION 3.15)
project(WeatherCliGui)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where vcpkg is
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
find_package(CURL REQUIRED)


add_executable(WeatherCliGui
    main.cpp
    weatherFrame.cpp
    weatherFetcher.cpp
)
target_link_libraries(WeatherCliGui ${wxWidgets_LIBRARIES} CURL::libcurl)
