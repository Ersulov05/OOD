#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Dance/DanceBehaviorFactory.h"
#include "Duck.h"
#include "Fly/FlyBehaviorFactory.h"
#include "Quack/QuackBehaviorFactory.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(createFlyWithWingsBehavior(), createQuackBehavior(), createWaltzDanceBehavior())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

#endif
