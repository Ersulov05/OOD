#pragma once

#include "../Canvas/ICanvas.h"
#include "../Common/Point.h"
#include "./Shape.h"
#include "./Style/FillStyle.h"
#include "./Style/OutlineStyle.h"
#include <vector>

class Triangle : public Shape
{
public:
	Triangle(
		const Frame& frame,
		OutlineStyle lineStyle,
		FillStyle fillStyle)
		: Shape(frame, lineStyle, fillStyle)
	{
	}

	std::string GetType() const
	{
		return "triangle";
	}

	void Draw(ICanvas& canvas) const override
	{
		Shape::Draw(canvas);
		auto frame = GetFrame();

		canvas.DrawPolygon(std::vector<Point>{
			{ frame.left + frame.width / 2, frame.top + frame.height / 2 },
			{ frame.left + frame.width, frame.top + frame.height },
			{ frame.left, frame.top + frame.height },
		});
	}
};