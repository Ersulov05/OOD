#pragma once

#include "./FlyBehavior.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

FlyBehavior createFlyNoWayBehavior()
{
	return FlyBehavior{
		[]() {},
		[]() { return 0; },
		[]() { return false; }
	};
}

FlyBehavior createFlyWithWingsBehavior()
{
	auto flyCounter = std::make_shared<int>(0);

	return FlyBehavior{
		[flyCounter]() mutable {
			++(*flyCounter);
			std::cout << "I'm flying with wings!!" << std::endl;
		},
		[flyCounter]() { return *flyCounter; },
		[]() { return true; }
	};
}
