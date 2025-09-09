#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Dance/DanceBehaviorFactory.h"
#include "Duck.h"
#include "Fly/FlyBehaviorFactory.h"
#include "Quack/QuackBehaviorFactory.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(createFlyNoWayBehavior(), createSqueakQuackBehavior(), createDanceNoWayBehavior())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}

	void Dance() override {}
};

#endif
