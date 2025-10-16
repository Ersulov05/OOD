#pragma once

#include "../../lib/Canvas/ICanvas.h"
#include <string>
#include <vector>

class MockCanvas : public ICanvas
{
public:
	void DrawEllipse(float cx, float cy, float rx, float ry)
	{
		auto shape = "ellipse " + m_color + " "
			+ std::to_string(cx) + " "
			+ std::to_string(cy) + " "
			+ std::to_string(rx) + " "
			+ std::to_string(ry);

		m_shapes.push_back(shape);
	}

	void DrawLine(float x1, float y1, float x2, float y2)
	{
		auto shape = "line " + m_color + " "
			+ std::to_string(x1) + " "
			+ std::to_string(y1) + " "
			+ std::to_string(x2) + " "
			+ std::to_string(y2);

		m_shapes.push_back(shape);
	}

	void SetColor(Color color)
	{
		m_color = ColorToString(color);
	}

	const std::vector<std::string> GetShapes() const
	{
		return m_shapes;
	}

private:
	std::vector<std::string> m_shapes;
	std::string m_color;
};