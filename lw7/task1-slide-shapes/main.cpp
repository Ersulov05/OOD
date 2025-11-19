#include "./lib/Canvas/CCanvas.h"
#include "./lib/Shape/Ellipse.h"
#include "./lib/Shape/GroupShapes.h"
#include "./lib/Shape/Rectangle.h"
#include "./lib/Shape/Style/FillStyle.h"
#include "./lib/Shape/Style/OutlineStyle.h"
#include "./lib/Shape/Triangle.h"
#include "./lib/Slide/Slide.h"
#include <iostream>
#include <memory>

const Color green = 0x00ff00ff;
const Color blue = 0x00ffffff;
const Color red = 0xff0000ff;
const Color black = 0x000000ff;
const Color brown = 0xe05200ff;
const Color yellow = 0xffff00ff;

std::unique_ptr<IShape> GetHome()
{
	GroupShapesList windowGroup;
	windowGroup.push_back(std::make_unique<Rectangle>(Frame(350, 450, 100, 100), OutlineStyle(brown, 7), FillStyle(blue)));
	windowGroup.push_back(std::make_unique<Rectangle>(Frame(395, 450, 10, 100), OutlineStyle(), FillStyle(brown)));
	windowGroup.push_back(std::make_unique<Rectangle>(Frame(350, 495, 100, 10), OutlineStyle(), FillStyle(brown)));

	auto window = std::make_unique<GroupShapes>(std::move(windowGroup));
	auto wall = std::make_unique<Rectangle>(Frame(300, 400, 200, 200), OutlineStyle(), FillStyle(green));
	auto roof = std::make_unique<Triangle>(Frame(300, 200, 200, 200), OutlineStyle(), FillStyle(red));

	GroupShapesList homeGroup;
	homeGroup.push_back(std::move(wall));
	homeGroup.push_back(std::move(roof));
	homeGroup.push_back(std::move(window));

	auto wall1 = std::make_unique<Rectangle>(Frame(0, 0, 0, 0), OutlineStyle(), FillStyle(green));
	auto wall2 = std::make_unique<Rectangle>(Frame(0, 0, 0, 0), OutlineStyle(), FillStyle(green));
	GroupShapesList homeGroup1;
	homeGroup1.push_back(std::move(wall1));
	homeGroup1.push_back(std::move(wall2));
	auto g1 = std::make_unique<GroupShapes>(std::move(homeGroup1));
	g1->SetFrame(Frame(1, 1, 1, 1));
	auto frame = g1->GetFrame();
	std::cout << frame.width << " " << frame.height << std::endl;
	return std::make_unique<GroupShapes>(std::move(homeGroup));
}

std::unique_ptr<IShape> GetSun()
{
	return std::make_unique<Ellipse>(Frame(50, 50, 100, 100), OutlineStyle(), FillStyle(yellow));
}

int main()
{
	CCanvas canvas;
	Slide slide(800, 600);

	slide.AddShape(std::make_unique<Rectangle>(Frame(0, 0, 800, 600), OutlineStyle(black), FillStyle()));
	slide.AddShape(GetHome());
	slide.AddShape(GetSun());

	slide.Draw(canvas);
	canvas.Save("test.svg");

	return 0;
}