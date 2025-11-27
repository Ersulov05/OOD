#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include <sstream>

TEST_CASE("GumballMachine initial state with gumballs")
{
	with_dynamic_state::GumballMachine machine(5);
	REQUIRE(machine.ToString().find("5 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("GumballMachine initial state sold out")
{
	with_dynamic_state::GumballMachine machine(0);
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("GumballMachine initial state with single gumball")
{
	with_dynamic_state::GumballMachine machine(1);
	REQUIRE(machine.ToString().find("1 gumball") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("Turn crank in HasQuarter state with multiple gumballs")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 4 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("Turn crank in HasQuarter state with multiple quarter")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	REQUIRE(machine.ToString().find("3 quarters") != std::string::npos);
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("4 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("2 quarters") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("Turn crank in HasQuarter state with last gumball")
{
	with_dynamic_state::GumballMachine machine(1);
	machine.InsertQuarter();
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("Turn crank in NoQuarter state")
{
	with_dynamic_state::GumballMachine machine(5);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 5 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("Turn crank in SoldOut state")
{
	with_dynamic_state::GumballMachine machine(0);
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	machine.TurnCrank();
	REQUIRE(machine.ToString().find("Inventory: 0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}
