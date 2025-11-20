#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include <sstream>
const std::string START_MACHINE_STATE = "waiting for quarter";

TEST_CASE("HasQuarterState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "No gumball dispensed\n");
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("HasQuarterState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	state.InsertQuarter(out);
	REQUIRE(out.str() == "You inserted a quarter\n");
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("HasQuarterState InsertQuarter more than 5 quarter")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("5 quarters") != std::string::npos);
	state.InsertQuarter(out);
	REQUIRE(out.str() == "You can't insert more than 5 quarter\n");
	REQUIRE(machine.ToString().find("5 quarters") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("HasQuarterState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	state.EjectQuarter(out);
	REQUIRE(out.str() == "0 quarter(s) returned\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("HasQuarterState Eject dont`t zero Quarter")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	state.EjectQuarter(out);
	REQUIRE(out.str() == "1 quarter(s) returned\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("HasQuarterState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned...\n");
	REQUIRE(machine.ToString().find("delivering a gumball") != std::string::npos);
}

TEST_CASE("HasQuarterState Refill")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.Refill(5, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("HasQuarterState Refill zero")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::HasQuarterState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.Refill(0, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}
