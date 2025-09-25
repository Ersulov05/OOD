#pragma once

#include "../lib/IObservable.h"
#include "../lib/WeatherData.h"
#include <iostream>
#include <string>

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(std::ostream& output, const std::string& id)
		: m_output(output)
		, m_id(id)
	{
	}

	int GetUpdateCount() const
	{
		return m_updateCount;
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_output << m_id;
		++m_updateCount;
	}

	int m_updateCount = 0;
	std::string m_id;
	std::ostream& m_output;
};