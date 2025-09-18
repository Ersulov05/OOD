#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Duck/Mocks/MockDanceBehavior.h"
#include "../lib/Duck/Mocks/MockDuck.h"
#include "../lib/Duck/Mocks/MockFlyBehavior.h"
#include "../lib/Duck/Mocks/MockQuackBehavior.h"

TEST_CASE("Test Dance at Duck")
{
	auto flyBehavior = createMockFlyBehavior(true);
	auto quackBehavior = createMockQuackBehavior(true);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(danceBehavior.getDanceCounter() == 0);
	duck.Dance();

	REQUIRE(danceBehavior.getDanceCounter() == 1);
}

TEST_CASE("Test Fly at Flyable Duck")
{
	auto flyBehavior = createMockFlyBehavior(true);
	auto quackBehavior = createMockQuackBehavior(true);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(flyBehavior.getFlyCounter() == 0);
	duck.Fly();

	REQUIRE(flyBehavior.getFlyCounter() == 1);
}

TEST_CASE("Test Fly at NotFlyable Duck")
{
	auto flyBehavior = createMockFlyBehavior(false);
	auto quackBehavior = createMockQuackBehavior(true);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(flyBehavior.getFlyCounter() == 0);
	duck.Fly();

	REQUIRE(flyBehavior.getFlyCounter() == 0);
}

TEST_CASE("Test Quack at Flyable and Quackable Duck")
{
	auto flyBehavior = createMockFlyBehavior(true);
	auto quackBehavior = createMockQuackBehavior(true);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(flyBehavior.getFlyCounter() == 0);
	REQUIRE(quackBehavior.getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 0);
	REQUIRE(flyBehavior.getFlyCounter() == 1);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 1);
	REQUIRE(flyBehavior.getFlyCounter() == 2);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 1);
	REQUIRE(flyBehavior.getFlyCounter() == 3);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 2);
	REQUIRE(flyBehavior.getFlyCounter() == 4);
}

TEST_CASE("Test Quack at NotFlyable and Quackable Duck")
{
	auto flyBehavior = createMockFlyBehavior(false);
	auto quackBehavior = createMockQuackBehavior(true);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(flyBehavior.getFlyCounter() == 0);
	REQUIRE(quackBehavior.getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 0);
	REQUIRE(flyBehavior.getFlyCounter() == 0);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 0);
	REQUIRE(flyBehavior.getFlyCounter() == 0);
}

TEST_CASE("Test Quack at Flyable and NotQuackable Duck")
{
	auto flyBehavior = createMockFlyBehavior(true);
	auto quackBehavior = createMockQuackBehavior(false);
	auto danceBehavior = createMockDanceBehavior();

	MockDuck duck(flyBehavior, quackBehavior, danceBehavior);

	REQUIRE(flyBehavior.getFlyCounter() == 0);
	REQUIRE(quackBehavior.getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 0);
	REQUIRE(flyBehavior.getFlyCounter() == 1);

	duck.Fly();
	REQUIRE(quackBehavior.getQuackCounter() == 0);
	REQUIRE(flyBehavior.getFlyCounter() == 2);
}