#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GumBallMachineWithDynamicallyCreatedState.h"
#include <sstream>

TEST_CASE("HasQuarterState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "You need to pay first\n");
}

TEST_CASE("HasQuarterState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	state.InsertQuarter(out);
	REQUIRE(out.str() == "You inserted a quarter\n");
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("HasQuarterState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	state.EjectQuarter(out);
	REQUIRE(out.str() == "You haven't inserted a quarter\n");
}

TEST_CASE("HasQuarterState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned but there's no quarter\n");
}
