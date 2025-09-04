#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Duck/Mocks/MockDuck.h"
#include "../lib/Duck/Mocks/MockFlyBehavior.h"
#include "../lib/Duck/Mocks/MockQuackBehavior.h"

TEST_CASE("Test Fly at Flyable Duck")
{
	auto flyBehavior = std::make_unique<MockFlyBehavior>(true);
	auto quackBehavior = std::make_unique<MockQuackBehavior>(true);

	auto* flyMock = flyBehavior.get();
	auto* quackMock = quackBehavior.get();

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior));

	REQUIRE(flyMock->getFlyCounter() == 0);
	duck.Fly();

	REQUIRE(flyMock->getFlyCounter() == 1);
}

TEST_CASE("Test Fly at NotFlyable Duck")
{
	auto flyBehavior = std::make_unique<MockFlyBehavior>(false);
	auto quackBehavior = std::make_unique<MockQuackBehavior>(true);

	auto* flyMock = flyBehavior.get();
	auto* quackMock = quackBehavior.get();

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior));

	REQUIRE(flyMock->getFlyCounter() == 0);
	duck.Fly();

	REQUIRE(flyMock->getFlyCounter() == 0);
}

TEST_CASE("Test Quack at Flyable and Quackable Duck")
{
	auto flyBehavior = std::make_unique<MockFlyBehavior>(true);
	auto quackBehavior = std::make_unique<MockQuackBehavior>(true);

	auto* flyMock = flyBehavior.get();
	auto* quackMock = quackBehavior.get();

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior));

	REQUIRE(flyMock->getFlyCounter() == 0);
	REQUIRE(quackMock->getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 0);
	REQUIRE(flyMock->getFlyCounter() == 1);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 1);
	REQUIRE(flyMock->getFlyCounter() == 2);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 1);
	REQUIRE(flyMock->getFlyCounter() == 3);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 2);
	REQUIRE(flyMock->getFlyCounter() == 4);
}

TEST_CASE("Test Quack at NotFlyable and Quackable Duck")
{
	auto flyBehavior = std::make_unique<MockFlyBehavior>(false);
	auto quackBehavior = std::make_unique<MockQuackBehavior>(true);

	auto* flyMock = flyBehavior.get();
	auto* quackMock = quackBehavior.get();

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior));

	REQUIRE(flyMock->getFlyCounter() == 0);
	REQUIRE(quackMock->getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 0);
	REQUIRE(flyMock->getFlyCounter() == 0);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 0);
	REQUIRE(flyMock->getFlyCounter() == 0);
}

TEST_CASE("Test Quack at Flyable and NotQuackable Duck")
{
	auto flyBehavior = std::make_unique<MockFlyBehavior>(true);
	auto quackBehavior = std::make_unique<MockQuackBehavior>(false);

	auto* flyMock = flyBehavior.get();
	auto* quackMock = quackBehavior.get();

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior));

	REQUIRE(flyMock->getFlyCounter() == 0);
	REQUIRE(quackMock->getQuackCounter() == 0);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 0);
	REQUIRE(flyMock->getFlyCounter() == 1);

	duck.Fly();
	REQUIRE(quackMock->getQuackCounter() == 0);
	REQUIRE(flyMock->getFlyCounter() == 2);
}