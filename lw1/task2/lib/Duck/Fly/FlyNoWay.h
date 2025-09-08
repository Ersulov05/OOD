#ifndef FLYNOWAY_H
#define FLYNOWAY_H

#include "IFlyBehavior.h"

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}

	int GetFlyCounter() const override
	{
		return 0;
	}

	bool IsFlyable() const override
	{
		return false;
	}
};

#endif
