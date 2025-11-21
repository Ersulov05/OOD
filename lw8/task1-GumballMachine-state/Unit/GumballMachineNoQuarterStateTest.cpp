#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GumBallMachineWithDynamicallyCreatedState.h"
#include <sstream>

TEST_CASE("NoQuarterState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.Dispense(out);
	REQUIRE(out.str() == "You need to pay first\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("NoQuarterState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.InsertQuarter(out);
	REQUIRE(out.str() == "You inserted a quarter\n");
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("NoQuarterState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.EjectQuarter(out);
	REQUIRE(out.str() == "You haven't inserted a quarter\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("NoQuarterState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::NoQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned but there's no quarter\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}
