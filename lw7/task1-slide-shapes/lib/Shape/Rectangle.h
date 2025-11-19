#pragma once

#include "../Canvas/ICanvas.h"
#include "../Common/Point.h"
#include "./Shape.h"
#include "./Style/FillStyle.h"
#include "./Style/OutlineStyle.h"
#include <vector>

class Rectangle : public Shape
{
public:
	Rectangle(
		const Frame& frame,
		OutlineStyle lineStyle,
		FillStyle fillStyle)
		: Shape(frame, std::move(lineStyle), std::move(fillStyle))
	{
	}

	std::string GetType() const
	{
		return "rectangle";
	}

	void Draw(ICanvas& canvas) const override
	{
		Shape::Draw(canvas);
		auto frame = GetFrame();

		canvas.DrawPolygon(std::vector<Point>{
			{ frame.left, frame.top },
			{ frame.left + frame.width, frame.top },
			{ frame.left + frame.width, frame.top + frame.height },
			{ frame.left, frame.top + frame.height },
		});
	}
};