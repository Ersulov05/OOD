#pragma once

#include "../WeatherData.h"
#include "Statistic.h"
#include "WindStatistic.h"
#include "WindUtils.h"
#include <iostream>

class CDisplay : private IObserver<SWeatherInfo>
	, private IObserver<SOutWeatherInfo>
{
public:
	CDisplay(IObservable<SWeatherInfo>& inObservable, int inPriority, IObservable<SOutWeatherInfo>& outObservable, int outPriority)
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
		std::cout << "in sensor" << std::endl;
		PrintBasicWeatherData(data);
		std::cout << "----------------" << std::endl;
	}

	void Update(SOutWeatherInfo const& data, IObservable<SOutWeatherInfo>& observable) override
	{
		std::cout << "out sensor" << std::endl;
		PrintBasicWeatherData(data);
		PrintWindStatistics(data);
		std::cout << "----------------" << std::endl;
	}

	void PrintWindStatistics(SOutWeatherInfo const& data) const
	{
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		if (data.windSpeed >= 1e-10)
		{
			std::cout << "Current Wind Direction " << DirectionToCardinal(data.windDirection) << std::endl;
		}
		else
		{
			std::cout << "Current Wind Direction Undefined" << std::endl;
		}
	}

	void PrintBasicWeatherData(SWeatherInfo const& data)
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
	}

	IObservable<SWeatherInfo>& m_inObservable;
	IObservable<SOutWeatherInfo>& m_outObservable;
};

class CStatDisplay : private IObserver<SWeatherInfo>
	, private IObserver<SOutWeatherInfo>
{
public:
	CStatDisplay(IObservable<SWeatherInfo>& inObservable, int inPriority, IObservable<SOutWeatherInfo>& outObservable, int outPriority)
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

		std::cout << "in sensor" << std::endl;
		PrintBasicStatistics();
		std::cout << "----------------" << std::endl;
	}

	void Update(SOutWeatherInfo const& data, IObservable<SOutWeatherInfo>& observable) override
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);
		m_windSpeedStats.Update(data.windSpeed);
		if (data.windSpeed >= 1e-10)
		{
			m_windDirectionStats.Update(data.windDirection);
		}

		std::cout << "out sensor" << std::endl;
		PrintBasicStatistics();
		PrintWindStatistics();
		std::cout << "----------------" << std::endl;
	}

	void PrintBasicStatistics() const
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
	}

	void PrintWindStatistics() const
	{
		std::cout << "Max Wind Speed " << m_windSpeedStats.GetMax() << std::endl;
		std::cout << "Min Wind Speed " << m_windSpeedStats.GetMin() << std::endl;
		std::cout << "Average Wind Speed " << m_windSpeedStats.GetAverage() << std::endl;
		double averageWindDirection = m_windDirectionStats.GetAverage();
		if (averageWindDirection < 0)
		{
			std::cout << "Average Wind Direction Undefined" << std::endl;
		}
		else
		{
			std::cout << "Average Wind Direction " << DirectionToCardinal(m_windDirectionStats.GetAverage()) << std::endl;
		}
	}

	CStatistic m_temperatureStats;
	CStatistic m_humidityStats;
	CStatistic m_pressureStats;
	CStatistic m_windSpeedStats;
	CWindStatistic m_windDirectionStats;
	IObservable<SWeatherInfo>& m_inObservable;
	IObservable<SOutWeatherInfo>& m_outObservable;
};