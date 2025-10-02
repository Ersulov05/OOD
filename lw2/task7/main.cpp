#include "./lib/Animal/AnimalData.h"
#include "./lib/Animal/Display.h"
#include "./lib/WeatherStation/Display/Display.h"
#include "./lib/WeatherStation/WeatherData.h"

int main()
{
	CAnimalData cat("cat");
	CAnimalData dog("dog");
	CAnimalData mouse("mouse");

	CAnimalDisplay animalDisplay;

	cat.RegisterObserver(animalDisplay, 1, AnimalEventType::ChangeHealth);
	dog.RegisterObserver(animalDisplay, 1, AnimalEventType::ChangeHealth);
	mouse.RegisterObserver(animalDisplay, 1, AnimalEventType::ChangeHealth);

	cat.SetEnergy(50);
	dog.SetHealth(90);
	mouse.SetHealth(10);

	// WeatherStation

	CWeatherData wd;

	CDisplay display;
	CDisplay display2;
	wd.RegisterObserver(display, 1, WeatherEventType::Temperature);
	wd.RegisterObserver(display, 1, WeatherEventType::Humidity);
	wd.RegisterObserver(display2, 2, WeatherEventType::Temperature);
	wd.RegisterObserver(display2, 2, WeatherEventType::Temperature);

	wd.SetTemperature(0);
	wd.SetTemperature(10);
	wd.SetHumidity(0.1);
	wd.SetPressure(761);

	return EXIT_SUCCESS;
}