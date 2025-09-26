#pragma once

#include "../lib/IObservable.h"
#include "../lib/WeatherData.h"
#include <iostream>
#include <string>

class CMockDisplay : private IObserver<SWeatherInfo>
{
public:
	CMockDisplay(IObservable<SWeatherInfo>& inObservable, int inPriority, IObservable<SWeatherInfo>& outObservable, int outPriority, std::ostream& output)
		: m_inObservable(inObservable)
		, m_outObservable(outObservable)
		, m_output(output)
	{
		inObservable.RegisterObserver(*this, inPriority);
		outObservable.RegisterObserver(*this, outPriority);
	}

	int GetUpdateCount() const
	{
		return m_updateCount;
	}

	~CMockDisplay()
	{
		m_inObservable.RemoveObserver(*this);
		m_outObservable.RemoveObserver(*this);
	}

private:
	void PrintSensorType(IObservable<SWeatherInfo>& observable) const
	{
		if (&observable == &m_inObservable)
		{
			m_output << "in sensor";
		}
		if (&observable == &m_outObservable)
		{
			m_output << "out sensor";
		}
	}

	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		PrintSensorType(observable);
		++m_updateCount;
	}

	int m_updateCount = 0;
	std::ostream& m_output;
	IObservable<SWeatherInfo>& m_inObservable;
	IObservable<SWeatherInfo>& m_outObservable;
};