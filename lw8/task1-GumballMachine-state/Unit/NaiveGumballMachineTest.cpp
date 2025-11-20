#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/NaiveGumBallMachine.h"
#include <sstream>

TEST_CASE("GumballMachine initial state with gumballs")
{
	naive::GumballMachine machine(5);
	REQUIRE(machine.ToString().find("Inventory: 5 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("GumballMachine initial state sold out")
{
	naive::GumballMachine machine(0);
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "sold out");
}

TEST_CASE("GumballMachine initial state with single gumball")
{
	naive::GumballMachine machine(1);
	REQUIRE(machine.ToString().find("Inventory: 1 gumball") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Insert quarter in NoQuarter state")
{
	naive::GumballMachine machine(5);
	REQUIRE(machine.GetState() == "waiting for quarter");
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "waiting for turn of crank");
}

TEST_CASE("Insert quarter in HasQuarter state")
{
	naive::GumballMachine machine(5);
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "waiting for turn of crank");
	machine.InsertQuarter(); // Second insert
	REQUIRE(machine.GetState() == "waiting for turn of crank");
}

TEST_CASE("Insert quarter in SoldOut state")
{
	naive::GumballMachine machine(0);
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "sold out");
}

TEST_CASE("Eject quarter in HasQuarter state")
{
	naive::GumballMachine machine(5);
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "waiting for turn of crank");
	machine.EjectQuarter();
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Eject quarter in NoQuarter state")
{
	naive::GumballMachine machine(5);
	REQUIRE(machine.GetState() == "waiting for quarter");
	machine.EjectQuarter();
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Eject quarter in SoldOut state")
{
	naive::GumballMachine machine(0);
	REQUIRE(machine.GetState() == "sold out");
	machine.EjectQuarter();
	REQUIRE(machine.GetState() == "sold out");
}

TEST_CASE("Turn crank in HasQuarter state with multiple gumballs")
{
	naive::GumballMachine machine(5);
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "waiting for turn of crank");
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 4 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Turn crank in HasQuarter state with last gumball")
{
	naive::GumballMachine machine(1);
	machine.InsertQuarter();
	REQUIRE(machine.GetState() == "waiting for turn of crank");
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "sold out");
}

TEST_CASE("Turn crank in NoQuarter state")
{
	naive::GumballMachine machine(5);
	REQUIRE(machine.GetState() == "waiting for quarter");
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 5 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Turn crank in SoldOut state")
{
	naive::GumballMachine machine(0);
	REQUIRE(machine.GetState() == "sold out");
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "sold out");
}

TEST_CASE("Refill sold out machine")
{
	naive::GumballMachine machine(0);
	REQUIRE(machine.GetState() == "sold out");

	machine.Refill(5);
	REQUIRE(machine.ToString().find("Inventory: 5 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Refill machine with gumballs")
{
	naive::GumballMachine machine(3);
	REQUIRE(machine.GetState() == "waiting for quarter");
	machine.Refill(10);
	REQUIRE(machine.ToString().find("Inventory: 10 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "waiting for quarter");
}

TEST_CASE("Refill to zero")
{
	naive::GumballMachine machine(5);
	REQUIRE(machine.GetState() == "waiting for quarter");
	machine.Refill(0);
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.GetState() == "sold out");
}
