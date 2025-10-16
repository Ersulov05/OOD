#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Exception/InvalidCountParametersException.h"
#include "../lib/Shape/ShapeStrategy/Exception/UncorrectCircleRadiusException.h"
#include "../lib/Shape/ShapeStrategy/Exception/UncorrectRectangleSizeException.h"
#include "../lib/Shape/ShapeStrategy/Exception/UncorrectTriangleException.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"
#include "../lib/Shape/ShapeStrategy/TriangleStrategy.h"

TEST_CASE("Test create Shape circle Strategy")
{
	std::vector<std::string> params = { "100", "50", "30" };
	auto strategy = CircleStrategy(params);

	REQUIRE(strategy.GetType() == "circle");
	REQUIRE(strategy.GetDescription() == "100.000000 50.000000 30.000000");
}

TEST_CASE("Test create Shape circle Strategy with Invalid count params")
{
	std::vector<std::string> params = { "100", "50", "30", "0" };
	REQUIRE_THROWS_AS(CircleStrategy(params), InvalidCountParametersException);

	params = {};
	REQUIRE_THROWS_AS(CircleStrategy(params), InvalidCountParametersException);
}

TEST_CASE("Test create Shape circle Strategy with Uncorrect circle Radius")
{
	std::vector<std::string> params = { "100", "50", "0" };
	REQUIRE_THROWS_AS(CircleStrategy(params), UncorrectCircleRadiusException);

	params = { "100", "50", "-1" };
	REQUIRE_THROWS_AS(CircleStrategy(params), UncorrectCircleRadiusException);
}

TEST_CASE("Test create Shape rectangle Strategy")
{
	std::vector<std::string> params = { "100", "50", "30", "20" };
	auto strategy = RectStrategy(params);

	REQUIRE(strategy.GetType() == "rectangle");
	REQUIRE(strategy.GetDescription() == "100.000000 50.000000 30.000000 20.000000");
}

TEST_CASE("Test create Shape rectangle Strategy with Invalid count params")
{
	std::vector<std::string> params = { "100", "50", "30", "0", "100" };
	REQUIRE_THROWS_AS(RectStrategy(params), InvalidCountParametersException);

	params = {};
	REQUIRE_THROWS_AS(RectStrategy(params), InvalidCountParametersException);
}

TEST_CASE("Test create Shape rectangle Strategy with Uncorrect Rectangle width")
{
	std::vector<std::string> params = { "100", "50", "0", "50" };
	REQUIRE_THROWS_AS(RectStrategy(params), UncorrectRectangleSizeException);

	params = { "100", "50", "-50", "50" };
	REQUIRE_THROWS_AS(RectStrategy(params), UncorrectRectangleSizeException);
}

TEST_CASE("Test create Shape rectangle Strategy with Uncorrect Rectangle height")
{
	std::vector<std::string> params = { "100", "50", "50", "0" };
	REQUIRE_THROWS_AS(RectStrategy(params), UncorrectRectangleSizeException);

	params = { "100", "50", "50", "-30" };
	REQUIRE_THROWS_AS(RectStrategy(params), UncorrectRectangleSizeException);
}

TEST_CASE("Test create Shape triangle Strategy")
{
	std::vector<std::string> params = { "100", "50", "30", "20", "10", "10" };
	auto strategy = TriangleStrategy(params);

	REQUIRE(strategy.GetType() == "triangle");
	REQUIRE(strategy.GetDescription() == "100.000000 50.000000 30.000000 20.000000 10.000000 10.000000");
}

TEST_CASE("Test create Shape triangle Strategy with Invalid count params")
{
	std::vector<std::string> params = { "100", "50", "30", "70", "100", "50", "70" };
	REQUIRE_THROWS_AS(TriangleStrategy(params), InvalidCountParametersException);

	params = {};
	REQUIRE_THROWS_AS(TriangleStrategy(params), InvalidCountParametersException);
}

TEST_CASE("Test create Shape triangle Strategy with Uncorrect Triangle")
{
	std::vector<std::string> params = { "100", "100", "100", "100", "100", "100" };
	REQUIRE_THROWS_AS(TriangleStrategy(params), UncorrectTriangleException);
}