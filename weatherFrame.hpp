//weatherFrame.hpp
#pragma once
#include <wx/wx.h>

class WeatherFrame : public wxFrame {
public:
    WeatherFrame();

private:
    wxTextCtrl* cityInput;
    wxStaticText* tempLabel;
    wxStaticText* humidityLabel;
    wxStaticText* windLabel;
    wxPanel* panel;	

    void OnGetWeather(wxCommandEvent& event);
};
