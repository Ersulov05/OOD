#ifndef FLYNOWAY_H
#define FLYNOWAY_H

#include "IFlyBehavior.h"

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}

	int getFlyCounter() override
	{
		return 0;
	}

	bool isFlyable() override
	{
		return false;
	}
};

#endif
