#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Designer/Designer.h"
#include "../lib/PictureDraft/PictureDraft.h"
#include "../lib/Shape/Factory/Exception/UnknownStringColorException.h"
#include "../lib/Shape/Factory/ShapeFactory.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Factory/Exception/UnknownShapeTypeException.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"
#include <sstream>

TEST_CASE("Test Designer Create PuctureDraft")
{
	auto designer = Designer();
	std::stringstream input;
	input.str("Red circle 100 100 100");
	auto pictureDraft = designer.CreateDraft(input);

	auto shapes = pictureDraft.ListShapes();

	REQUIRE(shapes.size() == 1);
	REQUIRE(shapes[0]->GetColor() == Color::Red);
	REQUIRE(shapes[0]->GetDescription() == "circle Red 100.000000 100.000000 100.000000");
}

TEST_CASE("Test Designer Create PuctureDraft MultiShapes")
{
	auto designer = Designer();
	std::stringstream input;
	input.str(
		"Red circle 100 100 100\nGreen rectangle 10 20 30 40\nBlue triangle 10 10 10 20 20 20\nYellow line 300 300 400 400\n");
	auto pictureDraft = designer.CreateDraft(input);

	auto shapes = pictureDraft.ListShapes();

	REQUIRE(shapes.size() == 4);
	REQUIRE(shapes[0]->GetColor() == Color::Red);
	REQUIRE(shapes[0]->GetDescription() == "circle Red 100.000000 100.000000 100.000000");
	REQUIRE(shapes[1]->GetColor() == Color::Green);
	REQUIRE(shapes[1]->GetDescription() == "rectangle Green 10.000000 20.000000 30.000000 40.000000");
	REQUIRE(shapes[2]->GetColor() == Color::Blue);
	REQUIRE(shapes[2]->GetDescription() == "triangle Blue 10.000000 10.000000 10.000000 20.000000 20.000000 20.000000");
	REQUIRE(shapes[3]->GetColor() == Color::Yellow);
	REQUIRE(shapes[3]->GetDescription() == "line Yellow 300.000000 300.000000 400.000000 400.000000");
}

TEST_CASE("Test Designer Create PuctureDraft MultiShapes exit key")
{
	auto designer = Designer();
	std::stringstream input;
	input.str(
		"Red circle 100 100 100\nGreen rectangle 10 20 30 40\nexit\nBlue triangle 10 10 10 20 20 20\nYellow line 300 300 400 400\n");
	auto pictureDraft = designer.CreateDraft(input);

	auto shapes = pictureDraft.ListShapes();

	REQUIRE(shapes.size() == 2);
	REQUIRE(shapes[0]->GetColor() == Color::Red);
	REQUIRE(shapes[0]->GetDescription() == "circle Red 100.000000 100.000000 100.000000");
	REQUIRE(shapes[1]->GetColor() == Color::Green);
	REQUIRE(shapes[1]->GetDescription() == "rectangle Green 10.000000 20.000000 30.000000 40.000000");
}