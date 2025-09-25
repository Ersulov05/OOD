#pragma once

#include "../lib/IObservable.h"
#include "../lib/WeatherData.h"

class CMockRemoveDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockRemoveDisplay(IObservable<SWeatherInfo>& observable)
		: m_observable(observable)
	{
	}

	int GetUpdateCount() const
	{
		return m_updateCount;
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		++m_updateCount;
		m_observable.RemoveObserver(*this);
	}

	int m_updateCount = 0;
	IObservable<SWeatherInfo>& m_observable;
};

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	int GetUpdateCount() const
	{
		return m_updateCount;
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		++m_updateCount;
	}

	int m_updateCount = 0;
};