#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Dance/DanceBehaviorFactory.h"
#include "Duck.h"
#include "Fly/FlyBehaviorFactory.h"
#include "Quack/QuackBehaviorFactory.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(createFlyNoWayBehavior(), createQuackBehavior(), createDanceNoWayBehavior())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

	void Dance() override {}
};

#endif
