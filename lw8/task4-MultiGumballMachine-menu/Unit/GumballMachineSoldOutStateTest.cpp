#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include <sstream>

const std::string START_MACHINE_STATE = "waiting for quarter";

TEST_CASE("SoldOutState Dispense")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "No gumball dispensed\n");
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("SoldOutState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.InsertQuarter(out);
	REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("SoldOutState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("0 quarters") != std::string::npos);
	state.EjectQuarter(out);
	REQUIRE(out.str() == "0 quarter(s) returned\n");
	REQUIRE(machine.ToString().find("0 quarters") != std::string::npos);
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("SoldOutState EjectQuarter with quarters")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
	state.EjectQuarter(out);
	REQUIRE(out.str() == "1 quarter(s) returned\n");
	REQUIRE(machine.ToString().find("0 quarters") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("SoldOutState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	state.TurnCrank(out);
	REQUIRE(out.str() == "You turned but there's no gumballs\n");
	REQUIRE(machine.ToString().find(START_MACHINE_STATE) != std::string::npos);
}

TEST_CASE("NoQuarterState Refill zero")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
	state.Refill(0, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
}

TEST_CASE("NoQuarterState Refill zero width quarters")
{
	with_dynamic_state::GumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
	state.Refill(0, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
}

TEST_CASE("NoQuarterState Refill width quarters")
{
	with_dynamic_state::GumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("0 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
	state.Refill(5, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("5 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
}

TEST_CASE("NoQuarterState Refill without quarters")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldOutState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
	REQUIRE(machine.ToString().find("0 quarters") != std::string::npos);
	state.Refill(5, out);
	REQUIRE(out.str() == "Refill\n");
	REQUIRE(machine.ToString().find("0 quarters") != std::string::npos);
	REQUIRE(machine.ToString().find("5 gumballs") != std::string::npos);
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}