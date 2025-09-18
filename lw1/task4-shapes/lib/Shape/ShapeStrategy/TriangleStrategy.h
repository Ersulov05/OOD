#pragma once

#include "../Point.h"
#include "./IShapeStrategy.h"

class TriangleStrategy : public IShapeStrategy
{
public:
	TriangleStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateParameters(parametrs);

		m_vertex1 = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_vertex2 = Point(std::stod(parametrs[2]), std::stod(parametrs[3]));
		m_vertex3 = Point(std::stod(parametrs[4]), std::stod(parametrs[5]));
	};

	std::string GetType() const override
	{
		return "triangle";
	}

	std::string GetDescription() const override
	{
		return "triangle description";
	};

	void Draw(ICanvas& canvas) const override
	{
		canvas.MoveTo(m_vertex1.x, m_vertex1.y);
		canvas.LineTo(m_vertex2.x, m_vertex2.y);
		canvas.LineTo(m_vertex3.x, m_vertex3.y);
		canvas.LineTo(m_vertex1.x, m_vertex1.y);
	};

	void MoveShape(double dx, double dy) override
	{
		m_vertex1.x += dx;
		m_vertex1.y += dy;
		m_vertex2.x += dx;
		m_vertex2.y += dy;
		m_vertex3.x += dx;
		m_vertex3.y += dy;
	}

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;

	void static ValidateParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 6)
		{
			throw std::invalid_argument("Invalid count arguments");
		}
	};
};