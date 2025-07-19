//weatherFrame.cpp
#include "weatherFrame.hpp"
#include "WeatherFetcher.hpp"
#include <wx/wx.h>

WeatherFrame::WeatherFrame()
    : wxFrame(nullptr, wxID_ANY, "Weather App", wxDefaultPosition, wxSize(500, 400)) {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    cityInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    vbox->Add(cityInput, 0, wxALL | wxALIGN_CENTER, 10);

    wxButton* getWeatherBtn = new wxButton(panel, wxID_ANY, "Get Weather");
    vbox->Add(getWeatherBtn, 0, wxALL | wxALIGN_CENTER, 5);

    // Add a spacer of 30 pixels
    vbox->AddSpacer(30);

    tempLabel = new wxStaticText(panel, wxID_ANY, "Temperature: ");
    humidityLabel = new wxStaticText(panel, wxID_ANY, "Humidity: ");
    windLabel = new wxStaticText(panel, wxID_ANY, "Wind Speed: ");

    vbox->Add(tempLabel, 0, wxALL | wxALIGN_CENTER, 5);
    vbox->Add(humidityLabel, 0, wxALL | wxALIGN_CENTER, 5);
    vbox->Add(windLabel, 0, wxALL | wxALIGN_CENTER, 5);

    panel->SetSizer(vbox);
    vbox->Fit(this);       // Adjust frame to content
    vbox->Layout();        // Apply layout
    this->Layout();        // Ensure frame layout
    std::cout << "wxWidgets Version: [" << wxVERSION_STRING << "]" << std::endl;
    getWeatherBtn->Bind(wxEVT_BUTTON, &WeatherFrame::OnGetWeather, this);
}

void WeatherFrame::OnGetWeather(wxCommandEvent& event) {
    std::string city = cityInput->GetValue().ToStdString();
    std::string apiKey = loadApiKey("../apikey.txt");
     if (apiKey.empty()) {
    wxMessageBox("API key not found! Make sure apikey.txt exists.", "Error", wxICON_ERROR);
    return;	;
}    
    std::string json = getWeatherData(city, apiKey);

    std::string temp = extract(json, "\"temp\"");
    std::string humidity = extract(json, "\"humidity\"");
    std::string wind = extract(json, "\"speed\"");

    std::cout << "Extracted Temp: [" << temp << "]" << std::endl;
    std::cout << "Extracted Humidity: [" << humidity << "]" << std::endl;
    std::cout << "Extracted Wind: [" << wind << "]" << std::endl;


 


    if (temp.empty()) {
        temp = "Not Found";
    }

    // Get the panel and sizer
    wxWindow* panel = this->GetChildren().Item(0)->GetData();
    wxBoxSizer* vbox = dynamic_cast<wxBoxSizer*>(panel->GetSizer());

    // Remove and recreate tempLabel without initial text, then set label
    vbox->Detach(tempLabel);
    tempLabel->Destroy();
    tempLabel = new wxStaticText(panel, wxID_ANY, "");
    tempLabel->SetLabel("Temperature: " + temp + " °C");
    vbox->Insert(3, tempLabel, 0, wxALL | wxALIGN_CENTER, 5); // Insert after spacer
    humidityLabel->SetLabel("Humidity: " + humidity + " %");
    windLabel->SetLabel("Wind Speed: " + wind + " m/s");

    // Ensure labels are visible
    tempLabel->Show(true);
    humidityLabel->Show(true);
    windLabel->Show(true);

    // Debug: Check label state
    std::cout << "Temp Label Text: [" << tempLabel->GetLabel() << "]" << std::endl;
    std::cout << "Temp Label Visible: [" << (tempLabel->IsShown() ? "Yes" : "No") << "]" << std::endl;
    std::cout << "Temp Label Address: [" << tempLabel << "]" << std::endl;

    // Force UI update
    this->Freeze();
    vbox->Layout();
    this->Layout();
    this->Refresh();
    this->Update();
    this->Thaw();
}
