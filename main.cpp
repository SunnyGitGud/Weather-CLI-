
#include <wx/wx.h>
#include "weatherFrame.hpp"

class WeatherApp : public wxApp {
public:
    virtual bool OnInit() {
        WeatherFrame* frame = new WeatherFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(WeatherApp);
