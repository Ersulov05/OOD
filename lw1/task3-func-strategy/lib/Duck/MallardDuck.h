#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Dance/DanceBehaviorFactory.h"
#include "Duck.h"
#include "Fly/FlyBehaviorFactory.h"
#include "Quack/QuackBehaviorFactory.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(createFlyWithWingsBehavior(), createQuackBehavior(), createMinuetDanceBehavior())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

#endif
