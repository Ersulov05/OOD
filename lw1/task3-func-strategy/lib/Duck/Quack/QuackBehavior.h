#pragma once

#include <algorithm>
#include <functional>

struct QuackBehavior
{
	std::function<void()> quack;
	std::function<bool()> isQuackable;
};
