#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Color/Color.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"

TEST_CASE("Test create Shape")
{
	std::vector<std::string> params = { "100", "50", "30" };
	auto strategy = std::make_unique<CircleStrategy>(params);

	Color color = Color::Green;
	auto shape = std::make_unique<shapes::Shape>(color, std::move(strategy));

	REQUIRE(shape->GetColor() == color);
	REQUIRE(shape->GetDescription() == "circle Green 100.000000 50.000000 30.000000");
}

TEST_CASE("Test create Shape")
{
	std::vector<std::string> params = { "100", "50", "30" };
	auto strategy = std::make_unique<CircleStrategy>(params);

	Color color = Color::Green;
	auto shape = std::make_unique<shapes::Shape>(color, std::move(strategy));

	REQUIRE(shape->GetColor() == color);
	REQUIRE(shape->GetDescription() == "circle Green 100.000000 50.000000 30.000000");
}

TEST_CASE("Test setColor Shape")
{
	std::vector<std::string> params = { "100", "50", "30" };
	auto strategy = std::make_unique<CircleStrategy>(params);

	std::string shapeId = "id";
	Color color = 0xffffff;
	auto shape = std::make_unique<shapes::Shape>(shapeId, color, std::move(strategy));

	REQUIRE(shape->GetId() == shapeId);
	REQUIRE(shape->GetColor() == color);

	Color newColor = 0xff00ff;
	shape->SetColor(newColor);

	REQUIRE(shape->GetColor() == newColor);
	REQUIRE(shape->GetId() == shapeId);
}