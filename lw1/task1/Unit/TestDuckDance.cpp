#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Duck/Mocks/MockDanceBehavior.h"
#include "../lib/Duck/Mocks/MockDuck.h"

TEST_CASE("Test Dance Duck")
{
	auto danceBehavior = std::make_unique<MockDanceBehavior>();
	auto* danceMock = danceBehavior.get();

	MockDuck duck(std::move(danceBehavior));

	REQUIRE(danceMock->getDanceCounter() == 0);

	duck.Dance();
	REQUIRE(danceMock->getDanceCounter() == 1);
}