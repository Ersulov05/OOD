#pragma once

#include "WindUtils.h"
#include <limits>

class CWindStatistic
{
public:
	void Update(double direction)
	{
		double rad = ToRadians(direction);
		m_sinAcc += sin(rad);
		m_cosAcc += cos(rad);

		++m_countAcc;
	}

	double GetAverage() const
	{
		if (m_sinAcc < 1e-10 && m_cosAcc < 1e-10)
		{
			return -1;
		}

		double avgRad = atan2(m_sinAcc, m_cosAcc);
		return NormalizeAngle(ToDegrees(avgRad));
	}

private:
	double m_sinAcc = 0;
	double m_cosAcc = 0;
	size_t m_countAcc = 0;
};