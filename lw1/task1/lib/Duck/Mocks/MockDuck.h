#pragma once

#include "../Dance/IDanceBehavior.h"
#include "../Duck.h"
#include "../Fly/FlyNoWay.h"
#include "../Quack/QuackBehavior.h"

class MockDuck : public Duck
{
public:
	MockDuck(std::unique_ptr<IDanceBehavior>&& danceBehavior)
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<QuackBehavior>(), std::move(danceBehavior))
	{
	}

	void Display() const override {}
};
