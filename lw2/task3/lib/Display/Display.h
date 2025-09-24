#pragma once

#include "../WeatherData.h"
#include "Statistic.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);

		PrintStatistics();
	}

	void PrintStatistics() const
	{
		std::cout << "Max Temp " << m_temperatureStats.GetMax() << std::endl;
		std::cout << "Min Temp " << m_temperatureStats.GetMin() << std::endl;
		std::cout << "Average Temp " << m_temperatureStats.GetAverage() << std::endl;
		std::cout << "Max Hum " << m_humidityStats.GetMax() << std::endl;
		std::cout << "Min Hum " << m_humidityStats.GetMin() << std::endl;
		std::cout << "Average Hum " << m_humidityStats.GetAverage() << std::endl;
		std::cout << "Max Pressure " << m_pressureStats.GetMax() << std::endl;
		std::cout << "Min Pressure " << m_pressureStats.GetMin() << std::endl;
		std::cout << "Average Pressure " << m_pressureStats.GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CStatistic m_temperatureStats;
	CStatistic m_humidityStats;
	CStatistic m_pressureStats;
};