#pragma once

#include "./DanceBehavior.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

DanceBehavior createDanceNoWayBehavior()
{
	return DanceBehavior{
		[]() {},
	};
}

DanceBehavior createWaltzDanceBehavior()
{
	return DanceBehavior{
		[]() {
			std::cout << "I'm dance waltz!!" << std::endl;
		},
	};
}

DanceBehavior createMinuetDanceBehavior()
{
	return DanceBehavior{
		[]() {
			std::cout << "I'm dance minuet!!" << std::endl;
		},
	};
}
