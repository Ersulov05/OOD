#pragma once

#include "Observer.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

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

class CStatistic
{
public:
	void Update(double value)
	{
		if (value < m_min)
		{
			m_min = value;
		}
		if (value > m_max)
		{
			m_max = value;
		}

		m_acc += value;
		++m_countAcc;
	}

	double GetMin() const
	{
		return m_min;
	}

	double GetMax() const
	{
		return m_max;
	}

	double GetAverage() const
	{
		return m_countAcc > 0
			? m_acc / m_countAcc
			: 0;
	}

private:
	double m_min = std::numeric_limits<double>::max();
	double m_max = std::numeric_limits<double>::min();
	double m_acc = 0.0;
	size_t m_countAcc = 0;
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

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const
	{
		return m_temperature;
	}

	double GetHumidity() const
	{
		return m_humidity;
	}

	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_temperature = temp;
		m_humidity = humidity;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};