#pragma once

#include "../Color/Color.h"
#include <iomanip>

namespace gfx
{
class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(float cx, float cy, float rx, float ry) = 0;
	virtual void DrawText(double left, double top, double fontSize, const std::string& text) = 0;
	virtual void SetColor(Color color) = 0;
};
} // namespace gfx
