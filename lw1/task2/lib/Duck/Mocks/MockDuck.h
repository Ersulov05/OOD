#pragma once

#include "../Duck.h"
#include "MockFlyBehavior.h"
#include "MockQuackBehavior.h"

class MockDuck : public Duck
{
public:
	MockDuck(
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior)
		: Duck(std::move(flyBehavior), std::move(quackBehavior))
	{
	}

	void Display() const override {}
};
