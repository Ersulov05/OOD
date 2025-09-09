#pragma once

#include "../Dance/DanceBehavior.h"
#include <algorithm>
#include <functional>
#include <memory>

struct MockDanceBehavior : public DanceBehavior
{
	std::function<int()> getDanceCounter;
};

MockDanceBehavior createMockDanceBehavior()
{
	auto danceCounter = std::make_shared<int>(0);

	return MockDanceBehavior{
		[danceCounter]() mutable {
			++(*danceCounter);
		},
		[danceCounter]() { return *danceCounter; }
	};
}
