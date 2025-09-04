#pragma once

#include "../Dance/IDanceBehavior.h"
#include <iostream>

class MockDanceBehavior : public IDanceBehavior
{
public:
	void Dance() const override
	{
		++m_danceCounter;
	}

	int const getDanceCounter() const
	{
		return m_danceCounter;
	}

private:
	mutable int m_danceCounter;
};
