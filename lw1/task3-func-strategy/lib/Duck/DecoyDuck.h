#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Dance/DanceBehaviorFactory.h"
#include "Duck.h"
#include "Fly/FlyBehaviorFactory.h"
#include "Quack/QuackBehaviorFactory.h"
#include <iostream>
#include <memory>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(createFlyNoWayBehavior(), createMuteQuackBehavior(), createDanceNoWayBehavior())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};

#endif
