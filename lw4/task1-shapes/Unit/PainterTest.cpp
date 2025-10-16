#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Designer/Designer.h"
#include "../lib/Painter/Painter.h"
#include "../lib/PictureDraft/PictureDraft.h"
#include "../lib/Shape/Factory/Exception/UnknownStringColorException.h"
#include "../lib/Shape/Factory/ShapeFactory.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Factory/Exception/UnknownShapeTypeException.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"
#include "./Mock/MockCanvas.h"
#include <sstream>

TEST_CASE("Test Painter Draw Ellipse")
{
	auto designer = Designer();
	auto painter = Painter();
	auto canvas = MockCanvas();
	std::stringstream input;
	input.str("Red circle 100 100 100");
	auto pictureDraft = designer.CreateDraft(input);

	painter.DrawPicture(pictureDraft, canvas);

	auto drawnShapes = canvas.GetShapes();

	REQUIRE(drawnShapes.size() == 1);
	REQUIRE(drawnShapes[0] == "ellipse Red 100.000000 100.000000 100.000000 100.000000");
}

TEST_CASE("Test Painter Draw Rectangle")
{
	auto designer = Designer();
	auto painter = Painter();
	auto canvas = MockCanvas();
	std::stringstream input;
	input.str("Green rectangle 10 20 30 40");
	auto pictureDraft = designer.CreateDraft(input);

	painter.DrawPicture(pictureDraft, canvas);

	auto drawnShapes = canvas.GetShapes();

	REQUIRE(drawnShapes.size() == 4);
	REQUIRE(drawnShapes[0] == "line Green 10.000000 20.000000 40.000000 20.000000");
	REQUIRE(drawnShapes[1] == "line Green 40.000000 20.000000 40.000000 -20.000000");
	REQUIRE(drawnShapes[2] == "line Green 40.000000 -20.000000 10.000000 -20.000000");
	REQUIRE(drawnShapes[3] == "line Green 10.000000 -20.000000 10.000000 20.000000");
}

TEST_CASE("Test Painter Draw Multi shapes")
{
	auto designer = Designer();
	auto painter = Painter();
	auto canvas = MockCanvas();
	std::stringstream input;
	input.str("Green rectangle 10 20 30 40\nRed circle 100 100 100");
	auto pictureDraft = designer.CreateDraft(input);

	painter.DrawPicture(pictureDraft, canvas);

	auto drawnShapes = canvas.GetShapes();

	REQUIRE(drawnShapes.size() == 5);
	REQUIRE(drawnShapes[0] == "line Green 10.000000 20.000000 40.000000 20.000000");
	REQUIRE(drawnShapes[1] == "line Green 40.000000 20.000000 40.000000 -20.000000");
	REQUIRE(drawnShapes[2] == "line Green 40.000000 -20.000000 10.000000 -20.000000");
	REQUIRE(drawnShapes[3] == "line Green 10.000000 -20.000000 10.000000 20.000000");
	REQUIRE(drawnShapes[4] == "ellipse Red 100.000000 100.000000 100.000000 100.000000");
}