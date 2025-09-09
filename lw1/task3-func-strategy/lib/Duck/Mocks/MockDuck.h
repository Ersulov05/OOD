#pragma once

#include "../Dance/DanceBehaviorFactory.h"
#include "../Duck.h"
#include "../Fly/FlyBehaviorFactory.h"
#include "../Quack/QuackBehaviorFactory.h"

#include "MockFlyBehavior.h"
#include "MockQuackBehavior.h"

class MockDuck : public Duck
{
public:
	MockDuck(
		FlyBehavior flyBehavior,
		QuackBehavior quackBehavior,
		DanceBehavior danceBehavior)
		: Duck(std::move(flyBehavior), std::move(quackBehavior), std::move(danceBehavior))
	{
	}

	void Display() const override {}
};
