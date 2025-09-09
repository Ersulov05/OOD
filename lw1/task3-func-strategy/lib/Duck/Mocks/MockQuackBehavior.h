#pragma once

#include "../Quack/QuackBehavior.h"

struct MockQuackBehavior : public QuackBehavior
{
	std::function<int()> getQuackCounter;
};

MockQuackBehavior createMockQuackBehavior(bool isQuackable)
{
	auto quackCounter = std::make_shared<int>(0);

	return MockQuackBehavior{
		[quackCounter]() mutable {
			++(*quackCounter);
		},
		[isQuackable]() { return isQuackable; },
		[quackCounter]() { return *quackCounter; }
	};
}
