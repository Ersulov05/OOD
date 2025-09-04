#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		++m_flyCounter;
		std::cout << "I'm flying with wings!!" << std::endl;
	}

	int getFlyCounter() const override
	{
		return m_flyCounter;
	}

	bool isFlyable() const override
	{
		return true;
	}

private:
	int m_flyCounter = 0;
};

#endif
