#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GumBallMachineWithDynamicallyCreatedState.h"
#include <sstream>

TEST_CASE("SoldOutState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "No gumball dispensed\n");
}

TEST_CASE("SoldOutState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.InsertQuarter(out);
	REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
}

TEST_CASE("SoldOutState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.EjectQuarter(out);
	REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
}

TEST_CASE("SoldOutState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned but there's no gumballs\n");
}
