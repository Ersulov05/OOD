#pragma once

#include "../Point.h"
#include "./Exception/InvalidCountParametersException.h"
#include "./Exception/UncorrectTriangleException.h"
#include "./IShapeStrategy.h"

class TriangleStrategy : public IShapeStrategy
{
public:
	TriangleStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateCountParameters(parametrs);

		m_vertex1 = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_vertex2 = Point(std::stod(parametrs[2]), std::stod(parametrs[3]));
		m_vertex3 = Point(std::stod(parametrs[4]), std::stod(parametrs[5]));
		AssertCorrectTriangle(m_vertex1, m_vertex2, m_vertex3);
	};

	std::string GetType() const override
	{
		return "triangle";
	}

	std::string GetDescription() const override
	{
		return std::to_string(m_vertex1.x) + " " + std::to_string(m_vertex1.y) + " "
			+ std::to_string(m_vertex2.x) + " " + std::to_string(m_vertex2.y) + " "
			+ std::to_string(m_vertex3.x) + " " + std::to_string(m_vertex3.y);
	};

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y);
		canvas.DrawLine(m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y);
		canvas.DrawLine(m_vertex3.x, m_vertex3.y, m_vertex1.x, m_vertex1.y);
	};

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;

	void static ValidateCountParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 6)
		{
			throw InvalidCountParametersException();
		}
	};

	double static GetArea(const Point& v1, const Point& v2, const Point& v3)
	{
		return std::abs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2;
	}

	void static AssertCorrectTriangle(const Point& v1, const Point& v2, const Point& v3)
	{
		if (GetArea(v1, v2, v3) < 1e-10)
		{
			throw UncorrectTriangleException();
		}
	}
};