#pragma once

#include "../WeatherData.h"
#include "WindUtils.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo, WeatherEventType>
{
private:
	void Update(SWeatherInfo const& data, WeatherEventType const& eventType) override
	{
		switch (eventType)
		{
		case WeatherEventType::Temperature:
			PrintTemperature(data);
			break;
		case WeatherEventType::Humidity:
			PrintHumidity(data);
			break;
		case WeatherEventType::Pressure:
			PrintPressure(data);
			break;
		case WeatherEventType::WindSpeed:
			PrintWindSpeed(data);
			break;
		case WeatherEventType::WindDirection:
			PrintWindDirection(data);
			break;
		default:
			PrintAllInfo(data);
			break;
		}
		std::cout << "----------------" << std::endl;
	}

	void PrintTemperature(SWeatherInfo const& data) const
	{
		std::cout << "Current Temp: " << data.temperature << std::endl;
	}

	void PrintPressure(SWeatherInfo const& data) const
	{
		std::cout << "Current Pressure: " << data.pressure << std::endl;
	}

	void PrintHumidity(SWeatherInfo const& data) const
	{
		std::cout << "Current Hum: " << data.humidity << std::endl;
	}

	void PrintWindSpeed(SWeatherInfo const& data) const
	{
		std::cout << "Current Wind Speed: " << data.windSpeed << std::endl;
	}

	void PrintWindDirection(SWeatherInfo const& data) const
	{
		if (data.windSpeed >= 1e-10)
		{
			std::cout << "Current Wind Direction " << DirectionToCardinal(data.windDirection) << std::endl;
		}
		else
		{
			std::cout << "Current Wind Direction Undefined" << std::endl;
		}
	}

	void PrintAllInfo(SWeatherInfo const& data) const
	{
		PrintTemperature(data);
		PrintHumidity(data);
		PrintPressure(data);
		PrintWindSpeed(data);
		PrintWindDirection(data);
	}
};