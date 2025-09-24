#pragma once

#include <limits>

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