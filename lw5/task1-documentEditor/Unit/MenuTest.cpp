#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Menu/Menu.h"

TEST_CASE("Test AddItem Menu Success")
{
	Menu menu(std::cin, std::cout);

	REQUIRE_NOTHROW(menu.AddItem("1", "1", [&](std::istringstream& params) {}));
}

TEST_CASE("Test AddItem Menu Fail Unique")
{
	Menu menu(std::cin, std::cout);

	menu.AddItem("1", "1", [&](std::istringstream& params) {});
	REQUIRE_THROWS(menu.AddItem("1", "1", [&](std::istringstream& params) {}));
}

TEST_CASE("Test Execute Command")
{
	Menu menu(std::cin, std::cout);

	int x = 0;
	menu.AddItem("1", "1", [&](std::istringstream& params) { x = 1; });

	menu.ExecuteCommand("1");
	REQUIRE(x == 1);
}

TEST_CASE("Test Execute Unknown command")
{
	Menu menu(std::cin, std::cout);

	REQUIRE_THROWS(menu.ExecuteCommand("2"));
}