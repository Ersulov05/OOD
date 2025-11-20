#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include <sstream>

TEST_CASE("SoldState Dispense with zero gumballs")
{
	with_dynamic_state::GumballMachine machine(0);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "Oops, out of gumballs\n");
	REQUIRE(machine.ToString().find("sold out") != std::string::npos);
}

TEST_CASE("SoldState Dispense with zero quarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	state.Dispense(out);
	REQUIRE(out.str() == "");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}

TEST_CASE("SoldState Dispense with don`t zero quarters")
{
	with_dynamic_state::GumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();

	with_dynamic_state::SoldState state(machine);
	std::stringstream out;
	REQUIRE(machine.ToString().find("2 quarter") != std::string::npos);
	state.Dispense(out);
	REQUIRE(machine.ToString().find("1 quarter") != std::string::npos);
	REQUIRE(out.str() == "");
	REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
}

TEST_CASE("SoldState InsertQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	state.InsertQuarter(out);
	REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
}

TEST_CASE("SoldState EjectQuarter")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	state.EjectQuarter(out);
	REQUIRE(out.str() == "Sorry you already turned the crank\n");
}

TEST_CASE("SoldState TurnCrank")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	state.TurnCrank(out);
	REQUIRE(out.str() == "Turning twice doesn't get you another gumball\n");
}

TEST_CASE("SoldState Refill")
{
	with_dynamic_state::GumballMachine machine(5);
	with_dynamic_state::SoldState state(machine);
	std::stringstream out;

	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
	state.Refill(5, out);
	REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
	REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
}
