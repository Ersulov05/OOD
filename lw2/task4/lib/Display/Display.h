#pragma once

#include "../WeatherData.h"
#include "Statistic.h"
#include <iostream>

class CDisplay : private IObserver<SWeatherInfo>
{
public:
	CDisplay(IObservable<SWeatherInfo>& inObservable, int inPriority, IObservable<SWeatherInfo>& outObservable, int outPriority)
		: m_inObservable(inObservable)
		, m_outObservable(outObservable)
	{
		inObservable.RegisterObserver(*this, inPriority);
		outObservable.RegisterObserver(*this, outPriority);
	}

	~CDisplay()
	{
		m_inObservable.RemoveObserver(*this);
		m_outObservable.RemoveObserver(*this);
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		PrintSensorType(observable);
		PrintWeatherData(data);
	}

	void PrintSensorType(IObservable<SWeatherInfo>& observable) const
	{
		if (&observable == &m_inObservable)
		{
			std::cout << "in sensor" << std::endl;
		}
		else
		{
			std::cout << "out sensor" << std::endl;
		}
	}

	void PrintWeatherData(SWeatherInfo const& data)
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	IObservable<SWeatherInfo>& m_inObservable;
	IObservable<SWeatherInfo>& m_outObservable;
};

class CStatDisplay : private IObserver<SWeatherInfo>
{
public:
	CStatDisplay(IObservable<SWeatherInfo>& inObservable, int inPriority, IObservable<SWeatherInfo>& outObservable, int outPriority)
		: m_inObservable(inObservable)
		, m_outObservable(outObservable)
	{
		inObservable.RegisterObserver(*this, inPriority);
		outObservable.RegisterObserver(*this, outPriority);
	}

	~CStatDisplay()
	{
		m_inObservable.RemoveObserver(*this);
		m_outObservable.RemoveObserver(*this);
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);

		PrintSensorType(observable);
		PrintStatistics();
	}

	void PrintSensorType(IObservable<SWeatherInfo>& observable) const
	{
		if (&observable == &m_inObservable)
		{
			std::cout << "in sensor" << std::endl;
		}
		else
		{
			std::cout << "out sensor" << std::endl;
		}
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
	IObservable<SWeatherInfo>& m_inObservable;
	IObservable<SWeatherInfo>& m_outObservable;
};