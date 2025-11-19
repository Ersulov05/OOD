#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Shape/Ellipse.h"
#include "../lib/Shape/GroupShapes.h"
#include "../lib/Shape/Rectangle.h"
#include "../lib/Shape/Style/FillStyle.h"
#include "../lib/Shape/Style/OutlineStyle.h"
#include "../lib/Shape/Triangle.h"

const Color green = 0x00ff00ff;

TEST_CASE("Test Create GroupShapes success")
{

	GroupShapesList group;
	group.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	group.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	REQUIRE_NOTHROW(GroupShapes(std::move(group)));
}

TEST_CASE("Test Create empty GroupShapes fail")
{
	GroupShapesList group;

	REQUIRE_THROWS(GroupShapes(std::move(group)));
}

TEST_CASE("Test Create GroupShapes with one shape fail")
{
	GroupShapesList group;
	group.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	REQUIRE_THROWS(GroupShapes(std::move(group)));
}

TEST_CASE("Test GroupShapes Add Shape")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 2);

	group.AddShape(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	REQUIRE(group.GetShapesCount() == 3);
}

TEST_CASE("Test GroupShapes Delete Shape By index success")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 3);

	group.DeleteShapeByIndex(2);
	REQUIRE(group.GetShapesCount() == 2);
}

TEST_CASE("Test GroupShapes Delete Shape By Index from the group of two shapes fail")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 2);
	REQUIRE_THROWS(group.DeleteShapeByIndex(0));
}

TEST_CASE("Test GroupShapes Delete Shape By dont exists index fail")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 3);
	REQUIRE_THROWS(group.DeleteShapeByIndex(3));
}

TEST_CASE("Test GroupShapes GetFrame")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 300, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 200), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto frame = group.GetFrame();

	REQUIRE(frame.left == 0);
	REQUIRE(frame.top == 0);
	REQUIRE(frame.width == 650);
	REQUIRE(frame.height == 550);
}

TEST_CASE("Test GroupShapes SetFrame")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(10, 20, 30, 40), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(50, 60, 70, 80), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto frame = group.GetFrame();

	REQUIRE(frame.left == 10);
	REQUIRE(frame.top == 20);
	REQUIRE(frame.width == 110);
	REQUIRE(frame.height == 120);

	group.SetFrame(Frame(0, 0, 1000, 2000));
	frame = group.GetFrame();
	REQUIRE(frame.left == 0);
	REQUIRE(frame.top == 0);
	REQUIRE(std::abs(frame.width - 1000) < 10e-4);
	REQUIRE(std::abs(frame.height - 2000) < 10e-4);
}

TEST_CASE("Test GroupShapes GetFillColor the group with shape fillColor = nullopt")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto fillColor = group.GetFillColor();

	REQUIRE(fillColor.has_value() == false);
}

TEST_CASE("Test GroupShapes GetOutlineColor the group with shape different fillColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xff)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xaa)));

	GroupShapes group(std::move(shapeList));
	auto fillColor = group.GetFillColor();

	REQUIRE(fillColor.has_value() == false);
}

TEST_CASE("Test GroupShapes GetOutlineColor the group with shape fillColor = 0xff")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xff)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xff)));

	GroupShapes group(std::move(shapeList));
	auto fillColor = group.GetFillColor();

	REQUIRE(fillColor.has_value() == true);
	REQUIRE(fillColor.value() == 0xff);
}

TEST_CASE("Test GroupShapes GetOutlineColor the group with shape outlineColor = nullopt")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto outlineColor = group.GetOutlineColor();

	REQUIRE(outlineColor.has_value() == false);
}

TEST_CASE("Test GroupShapes GetOutlineColor the group with shape different outlineColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0xff), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0xaa), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto outlineColor = group.GetOutlineColor();

	REQUIRE(outlineColor.has_value() == false);
}

TEST_CASE("Test GroupShapes GetOutlineColor the group with shape outlineColor = 0xff")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0xff), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0xff), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto outlineColor = group.GetOutlineColor();

	REQUIRE(outlineColor.has_value() == true);
	REQUIRE(outlineColor.value() == 0xff);
}

TEST_CASE("Test GetOutlineThickness the group with shape different OutlineThickness")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0, 1), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0, 2), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto outlineThickness = group.GetOutlineThickness();

	REQUIRE(outlineThickness == 0);
}

TEST_CASE("Test GetOutlineThickness the group with shape default OutlineThickness")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	auto outlineThickness = group.GetOutlineThickness();

	REQUIRE(outlineThickness == 1);
}

TEST_CASE("Test SetOutlineThickness the group with shape default OutlineThickness")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetOutlineThickness() == 1);

	group.SetOutlineThickness(3);
	REQUIRE(group.GetOutlineThickness() == 3);
}

TEST_CASE("Test SetOutlineThickness the group with shape different OutlineThickness")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0, 1), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0, 2), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetOutlineThickness() == 0);

	group.SetOutlineThickness(3);
	REQUIRE(group.GetOutlineThickness() == 3);
}

TEST_CASE("Test SetOutlineColor the group with shape outlineColor = nullopt")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetOutlineColor().has_value() == false);

	group.SetOutlineColor(0xff);
	REQUIRE(group.GetOutlineColor().has_value() == true);
	REQUIRE(group.GetOutlineColor().value() == 0xff);
}

TEST_CASE("Test SetOutlineColor the group with shape different outlineColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0xf1), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0xf2), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetOutlineColor().has_value() == false);

	group.SetOutlineColor(0xff);
	REQUIRE(group.GetOutlineColor().has_value() == true);
	REQUIRE(group.GetOutlineColor().value() == 0xff);
}

TEST_CASE("Test SetOutlineColor = nullopt, the group with shape same outlineColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(0xf1), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(0xf1), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetOutlineColor().has_value() == true);
	REQUIRE(group.GetOutlineColor().value() == 0xf1);

	group.SetOutlineColor(std::nullopt);
	REQUIRE(group.GetOutlineColor().has_value() == false);
}

TEST_CASE("Test SetFillColor the group with shape fillColor = nullopt")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle()));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle()));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetFillColor().has_value() == false);

	group.SetFillColor(0xff);
	REQUIRE(group.GetFillColor().has_value() == true);
	REQUIRE(group.GetFillColor().value() == 0xff);
}

TEST_CASE("Test SetFillColor the group with shape different fillColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf2)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetFillColor().has_value() == false);

	group.SetFillColor(0xff);
	REQUIRE(group.GetFillColor().has_value() == true);
	REQUIRE(group.GetFillColor().value() == 0xff);
}

TEST_CASE("Test SetFillColor = nullopt, the group with shape same fillColor")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetFillColor().has_value() == true);
	REQUIRE(group.GetFillColor().value() == 0xf1);

	group.SetFillColor(std::nullopt);
	REQUIRE(group.GetFillColor().has_value() == false);
}

TEST_CASE("Test GroupShapesByIndexes")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 3);
	group.GroupShapesByIndexes({ 0, 1 });
	REQUIRE(group.GetShapesCount() == 2);
	REQUIRE(group.GetShapeByIndex(1)->GetType() == "group");
}

TEST_CASE("Test GroupShapesByIndexes for GroupShapes with two elements")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 2);
	REQUIRE_THROWS(group.GroupShapesByIndexes({ 0, 1 }));
}

TEST_CASE("Test GroupShapesByIndexes grouping less then two elements")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 2);
	REQUIRE_THROWS(group.GroupShapesByIndexes({ 0 }));
}

TEST_CASE("Test GroupShapesByIndexes index out of range")
{
	GroupShapesList shapeList;
	shapeList.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(), FillStyle(0xf1)));
	shapeList.push_back(std::make_unique<Triangle>(Frame(0, 0, 100, 100), OutlineStyle(), FillStyle(0xf1)));

	GroupShapes group(std::move(shapeList));
	REQUIRE(group.GetShapesCount() == 2);
	REQUIRE_THROWS(group.GroupShapesByIndexes({ 3, 4 }));
}