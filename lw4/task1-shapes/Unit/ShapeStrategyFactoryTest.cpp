#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Shape/Factory/Exception/UnknownStringColorException.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Factory/Exception/UnknownShapeTypeException.h"
#include "../lib/Shape/ShapeStrategy/Factory/ShapeStrategyFactory.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"

TEST_CASE("Test create circle Shape Strategy")
{
	auto factory = ShapeStrategyFactory();

	auto shapeStrategy = factory.CreateShapeStrategy("circle", { "100", "100", "100" });
	REQUIRE(shapeStrategy->GetType() == "circle");
	REQUIRE(shapeStrategy->GetDescription() == "100.000000 100.000000 100.000000");
}

TEST_CASE("Test create rectangle Shape Strategy")
{
	auto factory = ShapeStrategyFactory();

	auto shapeStrategy = factory.CreateShapeStrategy("rectangle", { "100", "100", "100", "100" });
	REQUIRE(shapeStrategy->GetType() == "rectangle");
	REQUIRE(shapeStrategy->GetDescription() == "100.000000 100.000000 100.000000 100.000000");
}

TEST_CASE("Test create line Shape Strategy")
{
	auto factory = ShapeStrategyFactory();

	auto shapeStrategy = factory.CreateShapeStrategy("line", { "100", "100", "400", "100" });
	REQUIRE(shapeStrategy->GetType() == "line");
	REQUIRE(shapeStrategy->GetDescription() == "100.000000 100.000000 400.000000 100.000000");
}

TEST_CASE("Test create triangle Shape Strategy")
{
	auto factory = ShapeStrategyFactory();

	auto shapeStrategy = factory.CreateShapeStrategy("triangle", { "100", "100", "100", "150", "50", "50" });
	REQUIRE(shapeStrategy->GetType() == "triangle");
	REQUIRE(shapeStrategy->GetDescription() == "100.000000 100.000000 100.000000 150.000000 50.000000 50.000000");
}

TEST_CASE("Test create Shape Strategy with Unknown shape type")
{
	auto factory = ShapeStrategyFactory();

	REQUIRE_THROWS_AS(factory.CreateShapeStrategy("shapeType", {}), UnknownShapeTypeException);
}