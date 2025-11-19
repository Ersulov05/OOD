#pragma once

#include "../Canvas/ICanvas.h"
#include "./Shape.h"
#include "./Style/FillStyle.h"
#include "./Style/OutlineStyle.h"
#include <vector>

class Ellipse : public Shape
{
public:
	Ellipse(
		const Frame& frame,
		OutlineStyle lineStyle,
		FillStyle fillStyle)
		: Shape(frame, lineStyle, fillStyle)
	{
	}

	std::string GetType() const
	{
		return "ellipse";
	}

	void Draw(ICanvas& canvas) const override
	{
		Shape::Draw(canvas);
		auto frame = GetFrame();
		auto rx = frame.width / 2;
		auto ry = frame.height / 2;
		canvas.DrawEllipse(frame.left + rx, frame.top + ry, rx, ry);
	}
};