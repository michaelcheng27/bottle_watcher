#include "scale.h"
#include "logger.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

Scale::Scale()
{
}

void Scale::prepare()
{
    Logger::info("HX711 Demo");

    Logger::info("Initializing the scale");

    // Initialize library with data output pin, clock input pin and gain factor.
    // Channel selection is made by passing the appropriate gain:
    // - With a gain factor of 64 or 128, channel A is selected
    // - With a gain factor of 32, channel B is selected
    // By omitting the gain factor parameter, the library
    // default "128" (Channel A) is used here.
    scale_.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

    Logger::info("Before setting up the scale:");
    Logger::info("read: %f", scale_.read()); // print a raw reading from the ADC

    Logger::info("read average:  %f", scale_.read_average(20)); // print the average of 20 readings from the ADC

    Logger::info("get value: %f", scale_.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight (not set yet)

    Logger::info("get units: %f", scale_.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight (not set) divided
                                                           // by the SCALE parameter (not set yet)

    scale_.set_scale(461.04f); // this value is obtained by calibrating the scale with known weights; see the README for details
    scale_.tare();             // reset the scale to 0

    Logger::info("After setting up the scale:");

    Logger::info("read: %f", scale_.read()); // print a raw reading from the ADC

    Logger::info("read average: %f", scale_.read_average(20)); // print the average of 20 readings from the ADC

    Logger::info("get value: %f", scale_.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()

    Logger::info("get units: %f", scale_.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight, divided
                                                           // by the SCALE parameter set with set_scale
}

double Scale::read()
{
    return scale_.get_units(10);
}
