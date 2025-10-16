#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Shape/Factory/Exception/UnknownStringColorException.h"
#include "../lib/Shape/Factory/ShapeFactory.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Factory/Exception/UnknownShapeTypeException.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"

TEST_CASE("Test create circle Shape")
{
	auto factory = ShapeFactory();

	auto shape = factory.CreateShape({ "Red", "circle", "100", "100", "100" });
	REQUIRE(shape->GetColor() == Color::Red);
	REQUIRE(shape->GetDescription() == "circle Red 100.000000 100.000000 100.000000");
}

TEST_CASE("Test create rectangle Shape")
{
	auto factory = ShapeFactory();

	auto shape = factory.CreateShape({ "Green", "rectangle", "100", "100", "100", "100" });
	REQUIRE(shape->GetColor() == Color::Green);
	REQUIRE(shape->GetDescription() == "rectangle Green 100.000000 100.000000 100.000000 100.000000");
}

TEST_CASE("Test create line Shape")
{
	auto factory = ShapeFactory();

	auto shape = factory.CreateShape({ "Green", "line", "100", "100", "400", "100" });
	REQUIRE(shape->GetColor() == Color::Green);
	REQUIRE(shape->GetDescription() == "line Green 100.000000 100.000000 400.000000 100.000000");
}

TEST_CASE("Test create triangle Shape")
{
	auto factory = ShapeFactory();

	auto shape = factory.CreateShape({ "Green", "triangle", "100", "100", "100", "150", "50", "50" });
	REQUIRE(shape->GetColor() == Color::Green);
	REQUIRE(shape->GetDescription() == "triangle Green 100.000000 100.000000 100.000000 150.000000 50.000000 50.000000");
}

TEST_CASE("Test create Shape with Unknown color")
{
	auto factory = ShapeFactory();
	std::vector<std::string> params = { "NoColor", "circle", "100", "100", "100" };

	REQUIRE_THROWS_AS(factory.CreateShape(params), UnknownStringColorException);
}

TEST_CASE("Test create Shape with Unknown shape type")
{
	auto factory = ShapeFactory();
	std::vector<std::string> params = { "Red", "shapeType", "100", "100", "100" };

	REQUIRE_THROWS_AS(factory.CreateShape(params), UnknownShapeTypeException);
}