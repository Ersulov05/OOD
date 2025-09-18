#pragma once

#include "../Point.h"
#include "./IShapeStrategy.h"

class RectStrategy : public shapes::IShapeStrategy
{
public:
	RectStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateParameters(parametrs);

		m_topLeft = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_width = std::stod(parametrs[2]);
		m_height = std::stod(parametrs[3]);
	};

	std::string GetType() const override
	{
		return "rectangle";
	}

	std::string GetDescription() const override
	{
		return "rectangle description";
	};

	void Draw(gfx::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_topLeft.x, m_topLeft.y);
		canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);
		canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y - m_height);
		canvas.LineTo(m_topLeft.x, m_topLeft.y - m_height);
		canvas.LineTo(m_topLeft.x, m_topLeft.y);
	};

	void MoveShape(double dx, double dy) override
	{
		m_topLeft.x += dx;
		m_topLeft.y += dy;
	}

private:
	Point m_topLeft;
	double m_width;
	double m_height;

	void static ValidateParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 4)
		{
			throw std::invalid_argument("Invalid count arguments");
		}
	};
};