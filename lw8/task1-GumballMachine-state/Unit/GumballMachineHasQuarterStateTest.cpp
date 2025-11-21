#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GumBallMachineWithDynamicallyCreatedState.h"
#include <sstream>

TEST_CASE("HasQuarterState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	state.Dispense(out);
	REQUIRE(out.str() == "No gumball dispensed\n");
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("HasQuarterState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	state.InsertQuarter(out);
	REQUIRE(out.str() == "You can't insert another quarter\n");
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("HasQuarterState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	state.EjectQuarter(out);
	REQUIRE(out.str() == "Quarter returned\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("HasQuarterState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned...\n");
	REQUIRE(machine.ToString().find("delivering a gumball") != std::string::npos);
}
