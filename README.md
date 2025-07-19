# 🌤️ Weather GUI App (C++ + wxWidgets)

A simple weather application with a graphical interface, written in **C++** using **wxWidgets** and **CMake**. It fetches live weather data from OpenWeatherMap using `libcurl`.

---
## 📦 Requirements

- C++17 or higher
- [CMake](https://cmake.org/) ≥ 3.10
- [wxWidgets](https://www.wxwidgets.org/) ≥ 3.2
- `libcurl` for HTTP requests

### 📥 Ubuntu/Debian Setup

```bash
sudo apt update
sudo apt install g++ cmake libwxgtk3.2-dev libcurl4-openssl-dev
```

---

## 🔐 API Key Setup

This app requires an API key from [OpenWeatherMap](https://openweathermap.org/api).

1. **Get your API key** from OpenWeatherMap.
2. **Create a file** in the root of the project named `apikey.txt`.
3. **Paste your key** into the file — it should look like:

   ```
   abcdef1234567890yourapikey
   ```

## ⚙️ Build Instructions

### 🔧 Step-by-step Manual Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

If CMake doesn’t find `wxWidgets` or `curl`, you may need to specify paths:

```bash
cmake .. \
  -DwxWidgets_CONFIG_EXECUTABLE=/usr/bin/wx-config \
  -DCURL_INCLUDE_DIR=/usr/include \
  -DCURL_LIBRARY=/usr/lib/x86_64-linux-gnu/libcurl.so
```

---

### ▶️ Running the App

> **Important:** Run the app from the project root, so it can read `apikey.txt`.

```bash
./build/WeatherCliGui
```

---

## 📁 Project Structure

```
.
├── CMakeLists.txt
├── main.cpp
├── weatherFetcher.cpp / .hpp
├── weatherFrame.cpp / .hpp
├── apikey.txt              # <-- your private API key (not shared)
├── apikey.txt.example      # optional example for others
├── build/                  # CMake build output (ignored)
└── README.md
```

