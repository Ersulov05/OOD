#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Color/Color.h"
#include "../lib/Picture/Exception/ShapeDontUniqueIdException.h"
#include "../lib/Picture/Picture.h"
#include "../lib/Shape/Shape.h"
#include "../lib/Shape/ShapeStrategy/CircleStrategy.h"
#include "../lib/Shape/ShapeStrategy/IShapeStrategy.h"
#include "../lib/Shape/ShapeStrategy/RectStrategy.h"

std::unique_ptr<shapes::IShapeStrategy> GetDefaultShapeStrategy()
{
	std::vector<std::string> params = { "100", "50", "30" };
	return std::make_unique<CircleStrategy>(params);
}

std::unique_ptr<shapes::Shape> GetDefaultShape(const std::string& shapeId)
{
	auto strategy = GetDefaultShapeStrategy();

	Color color = 0xffffff;
	return std::make_unique<shapes::Shape>(shapeId, color, std::move(strategy));
}

TEST_CASE("Test addShape to Picture")
{
	shapes::Picture picture;
	REQUIRE(picture.ListShapes().size() == 0);

	auto shape1 = GetDefaultShape("1");
	picture.AddShape(std::move(shape1));
	REQUIRE(picture.ListShapes().size() == 1);

	auto shape2 = GetDefaultShape("2");
	picture.AddShape(std::move(shape2));
	REQUIRE(picture.ListShapes().size() == 2);
}

TEST_CASE("Test addShape to Picture Not unique Id Fail")
{
	shapes::Picture picture;
	REQUIRE(picture.ListShapes().size() == 0);

	auto shape1 = GetDefaultShape("1");
	picture.AddShape(std::move(shape1));

	auto shape2 = GetDefaultShape("1");
	REQUIRE_THROWS_AS(picture.AddShape(std::move(shape2)), ShapeDontUniqueIdException);
}

TEST_CASE("Test deleteShape to Picture success")
{
	shapes::Picture picture;
	REQUIRE(picture.ListShapes().size() == 0);

	auto shape = GetDefaultShape("1");
	picture.AddShape(std::move(shape));
	REQUIRE(picture.ListShapes().size() == 1);

	picture.DeleteShape("1");
	REQUIRE(picture.ListShapes().size() == 0);
}

TEST_CASE("Test deleteShape to Picture empty shapes success")
{
	shapes::Picture picture;

	REQUIRE_NOTHROW(picture.DeleteShape("1"));
}

TEST_CASE("Test ChangeShapeColor to Picture success")
{
	shapes::Picture picture;
	REQUIRE(picture.ListShapes().size() == 0);
	std::string shapeId = "1";
	auto shape = GetDefaultShape("1");
	picture.AddShape(std::move(shape));
	REQUIRE(picture.ListShapes()[0]->GetColor() == 0xffffff);

	picture.ChangeShapeColor(shapeId, 0x000000);

	REQUIRE(picture.ListShapes()[0]->GetColor() == 0x000000);
}

TEST_CASE("Test ChangeShapeColor to Picture shapeNotFound fail")
{
	shapes::Picture picture;

	REQUIRE_THROWS_AS(picture.ChangeShapeColor("id", 0x000000), ShapeNotFoundException);
}

TEST_CASE("Test ChangeShapeStrategy to Picture shapeNotFound fail")
{
	shapes::Picture picture;
	auto strategy = GetDefaultShapeStrategy();

	REQUIRE_THROWS_AS(picture.ChangeShapeStrategy("id", std::move(strategy)), ShapeNotFoundException);
}

TEST_CASE("Test MoveShape to Picture success")
{
	shapes::Picture picture;
	std::string shapeId = "1";
	auto shape = GetDefaultShape("1");
	picture.AddShape(std::move(shape));

	REQUIRE(picture.ListShapes()[0]->GetDescription() == "circle 1 #ffffff 100.000000 50.000000 30.000000");

	picture.MoveShape(shapeId, 100, 100);

	REQUIRE(picture.ListShapes()[0]->GetDescription() == "circle 1 #ffffff 200.000000 150.000000 30.000000");
}

TEST_CASE("Test MoveShape to Picture shapeNotFound fail")
{
	shapes::Picture picture;

	REQUIRE_THROWS_AS(picture.MoveShape("id", 100, 100), ShapeNotFoundException);
}

TEST_CASE("Test MovePicture to Picture success")
{
	shapes::Picture picture;
	std::string shapeId = "1";
	auto shape = GetDefaultShape("1");
	picture.AddShape(std::move(shape));

	REQUIRE(picture.ListShapes()[0]->GetDescription() == "circle 1 #ffffff 100.000000 50.000000 30.000000");

	picture.MovePicture(100, 100);

	REQUIRE(picture.ListShapes()[0]->GetDescription() == "circle 1 #ffffff 200.000000 150.000000 30.000000");
}