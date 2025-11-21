#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GumBallMachineWithDynamicallyCreatedState.h"
#include <sstream>

TEST_CASE("SoldOutState Dispense")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	state.Dispense(out);
	REQUIRE(out.str() == "No gumball dispensed\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("SoldOutState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	state.InsertQuarter(out);
	REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("SoldOutState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	state.EjectQuarter(out);
	REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("SoldOutState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned but there's no gumballs\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}
