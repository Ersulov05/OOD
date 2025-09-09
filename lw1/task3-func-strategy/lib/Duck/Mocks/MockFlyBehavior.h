#pragma once

#include "../Fly/FlyBehavior.h"

FlyBehavior createMockFlyBehavior(bool isFlyable)
{
	auto flyCounter = std::make_shared<int>(0);

	return FlyBehavior{
		[flyCounter]() mutable {
			++(*flyCounter);
		},
		[flyCounter]() { return *flyCounter; },
		[isFlyable]() { return isFlyable; }
	};
}
