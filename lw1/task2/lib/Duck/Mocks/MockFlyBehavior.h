#pragma once

#include "../Fly/IFlyBehavior.h"
#include <iostream>

class MockFlyBehavior : public IFlyBehavior
{
public:
	MockFlyBehavior(bool flyable = true)
		: m_flyable(flyable){};

	void Fly() override
	{
		++m_flyCounter;
	}

	int getFlyCounter() const override
	{
		return m_flyCounter;
	}

	bool isFlyable() const override
	{
		return m_flyable;
	}

private:
	int m_flyCounter = 0;
	bool m_flyable;
};
