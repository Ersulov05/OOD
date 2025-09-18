#pragma once

#include "../Point.h"
#include "./IShapeStrategy.h"

class LineStrategy : public shapes::IShapeStrategy
{
public:
	LineStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateParameters(parametrs);

		m_start = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_end = Point(std::stod(parametrs[2]), std::stod(parametrs[3]));
	};

	std::string GetType() const override
	{
		return "line";
	}

	std::string GetDescription() const override
	{
		return "line description";
	};

	void Draw(gfx::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_start.x, m_start.y);
		canvas.LineTo(m_end.x, m_end.y);
	};

	void MoveShape(double dx, double dy) override
	{
		m_start.x += dx;
		m_start.y += dy;
		m_end.x += dx;
		m_end.y += dy;
	}

private:
	Point m_start;
	Point m_end;

	void static ValidateParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 4)
		{
			throw std::invalid_argument("Invalid count arguments");
		}
	};
};