#pragma once

#include <algorithm>
#include <functional>

struct FlyBehavior
{
	std::function<void()> fly;
	std::function<int()> getFlyCounter;
	std::function<bool()> isFlyable;
};
