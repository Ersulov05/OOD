#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/WeatherData.h"
#include "./MockDisplay.h"

TEST_CASE("Test Empty Notify Observer")
{
	CWeatherData wd;

	REQUIRE_NOTHROW(wd.NotifyObservers());
}

TEST_CASE("Test Notify Observer")
{
	CWeatherData wd;

	CMockRemoveDisplay display(wd);
	wd.RegisterObserver(display);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);

	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
}

TEST_CASE("Test Multi Notify Observer")
{
	CWeatherData wd;

	CMockRemoveDisplay display(wd);
	CMockRemoveDisplay display2(wd);
	wd.RegisterObserver(display);
	wd.RegisterObserver(display2);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE(display2.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(display2.GetUpdateCount() == 1);

	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(display2.GetUpdateCount() == 1);
}

TEST_CASE("Test duplicate observer registration")
{
	CWeatherData wd;
	CMockDisplay display;

	wd.RegisterObserver(display);
	wd.RegisterObserver(display);

	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
}

TEST_CASE("Test removal of non-existent observer")
{
	CWeatherData wd;
	CMockDisplay anotherDisplay;

	REQUIRE_NOTHROW(wd.RemoveObserver(anotherDisplay));
}
