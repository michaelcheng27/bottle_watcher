#include "HX711.h"
class Scale
{
public:
    Scale();
    void prepare();
    double read();

private:
    HX711 scale_;
};