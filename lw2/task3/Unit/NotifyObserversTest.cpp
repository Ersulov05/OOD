#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/WeatherData.h"
#include "./MockDisplay.h"
#include <sstream>

TEST_CASE("Test Empty Notify Observer")
{
	CWeatherData wd;

	REQUIRE_NOTHROW(wd.NotifyObservers());
}

TEST_CASE("Test Notify Observer")
{
	CWeatherData wd;

	std::stringstream stream;
	CMockDisplay display(stream, "1");
	wd.RegisterObserver(display, 2);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(stream.str() == "1");
}

TEST_CASE("Test Multi Notify Observer")
{
	CWeatherData wd;
	std::stringstream stream;

	CMockDisplay display(stream, "1");
	CMockDisplay display2(stream, "2");
	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(display2, 10);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE(display2.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(stream.str() == "21");
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(display2.GetUpdateCount() == 1);
}

TEST_CASE("Test duplicate observer registration")
{
	CWeatherData wd;
	std::stringstream stream;
	CMockDisplay display(stream, "1");
	CMockDisplay display2(stream, "2");

	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(display2, 2);
	REQUIRE_NOTHROW(wd.RegisterObserver(display, 10));

	REQUIRE_NOTHROW(wd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(display2.GetUpdateCount() == 1);
	REQUIRE(stream.str() == "21");
}
