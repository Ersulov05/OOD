#pragma once

#include "../Common/Color.h"
#include "../Common/Point.h"
#include <iomanip>
#include <optional>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
	virtual void DrawPolygon(std::vector<Point> points) = 0;
	virtual void DrawEllipse(float cx, float cy, float rx, float ry) = 0;
	virtual void SetThickness(size_t thickness) = 0;
	virtual void SetOutlineColor(std::optional<Color> color) = 0;
	virtual void SetFillColor(std::optional<Color> color) = 0;
	virtual void SetWidth(size_t width) = 0;
	virtual void SetHeight(size_t height) = 0;
	virtual void Clear() = 0;
};
