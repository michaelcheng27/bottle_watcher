#include "scale.h"
#include "wifi_manager.h"

class SmartScale
{
public:
    SmartScale(Scale scale， WifiManager wifiManager){};

private:
    Scale &scale_;
    WifiManager &wifiManager_;
};