#pragma once

#include "../Point.h"
#include "./Exception/InvalidCountParametersException.h"
#include "./Exception/UncorrectCircleRadiusException.h"
#include "./IShapeStrategy.h"

class CircleStrategy : public shapes::IShapeStrategy
{
public:
	CircleStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateCountParameters(parametrs);

		m_radius = std::stod(parametrs[2]);
		AssertCorrectRadius(m_radius);
		m_center = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
	};

	std::string GetType() const override
	{
		return "circle";
	}

	std::string GetDescription() const override
	{
		return "circle description";
	};

	void Draw(gfx::ICanvas& canvas) const override
	{
		canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
	};

	void MoveShape(double dx, double dy) override
	{
		m_center.x += dx;
		m_center.y += dy;
	}

private:
	Point m_center;
	double m_radius;

	void static ValidateCountParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 3)
		{
			throw InvalidCountParametersException();
		}
	};

	void static AssertCorrectRadius(double m_radius)
	{
		if (m_radius <= 0)
		{
			throw UncorrectCircleRadiusException();
		}
	}
};