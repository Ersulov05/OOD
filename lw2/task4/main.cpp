#include "./lib/Display/Display.h"
#include "./lib/WeatherData.h"

int main()
{
	CWeatherData wd;
	CWeatherData wd2;

	CDisplay display(wd, 1, wd2, 1);

	CStatDisplay statDisplay(wd, 2, wd2, 3);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd2.SetMeasurements(3, 0.7, 760);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);

	return EXIT_SUCCESS;
}