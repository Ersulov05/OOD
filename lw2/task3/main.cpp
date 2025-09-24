#include "./lib/Display/Display.h"
#include "./lib/WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 1);

	CStatDisplay statDisplay;
	wd.RegisterObserver(statDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RegisterObserver(statDisplay, 3);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);

	return EXIT_SUCCESS;
}