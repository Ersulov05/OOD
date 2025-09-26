#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/WeatherData.h"
#include "./MockDisplay.h"
#include <sstream>

TEST_CASE("Test Notify Observer duo sensor")
{
	CWeatherData inWd;
	CWeatherData outWd;

	std::stringstream stream;
	CMockDisplay display(inWd, 2, outWd, 3, stream);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(inWd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(stream.str() == "in sensor");

	REQUIRE_NOTHROW(outWd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 2);
	REQUIRE(stream.str() == "in sensorout sensor");
}

TEST_CASE("Test Multi Notify Observer")
{
	CWeatherData inWd;
	CWeatherData outWd;

	std::stringstream stream;
	CMockDisplay display(inWd, 2, outWd, 3, stream);
	CMockDisplay display2(inWd, 2, outWd, 3, stream);

	REQUIRE(display.GetUpdateCount() == 0);
	REQUIRE_NOTHROW(inWd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 1);
	REQUIRE(display2.GetUpdateCount() == 1);
	REQUIRE(stream.str() == "in sensorin sensor");

	REQUIRE_NOTHROW(outWd.NotifyObservers());
	REQUIRE(display.GetUpdateCount() == 2);
	REQUIRE(display2.GetUpdateCount() == 2);
	REQUIRE(stream.str() == "in sensorin sensorout sensorout sensor");
}