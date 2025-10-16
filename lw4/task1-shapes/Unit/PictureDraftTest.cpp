#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/PictureDraft/PictureDraft.h"
#include "../lib/Shape/Factory/Exception/UnknownStringColorException.h"
#include "../lib/Shape/Factory/ShapeFactory.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/Factory/Exception/UnknownShapeTypeException.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"

TEST_CASE("Test PuctureDraft List Shapes")
{
	auto pictureDraft = PictureDraft();
	auto shapes = pictureDraft.ListShapes();

	REQUIRE(shapes.size() == 0);
}

TEST_CASE("Test PicktureDraft Add Shape")
{
	auto factory = ShapeFactory();
	auto pictureDraft = PictureDraft();
	auto shape = factory.CreateShape({ "Red", "circle", "100", "100", "100" });

	pictureDraft.AddShape(std::move(shape));
	auto shapes = pictureDraft.ListShapes();

	REQUIRE(shapes.size() == 1);
	REQUIRE(shapes[0]->GetColor() == Color::Red);
	REQUIRE(shapes[0]->GetDescription() == "circle Red 100.000000 100.000000 100.000000");
}