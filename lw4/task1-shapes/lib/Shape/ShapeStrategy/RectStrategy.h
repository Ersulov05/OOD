#pragma once

#include "../Point.h"
#include "./Exception/InvalidCountParametersException.h"
#include "./Exception/UncorrectRectangleSizeException.h"
#include "./IShapeStrategy.h"

class RectStrategy : public IShapeStrategy
{
public:
	RectStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateCountParameters(parametrs);

		m_topLeft = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_width = std::stod(parametrs[2]);
		m_height = std::stod(parametrs[3]);
		AssertCorrectRectangleSize(m_width, m_height);
	};

	std::string GetType() const override
	{
		return "rectangle";
	}

	std::string GetDescription() const override
	{
		return std::to_string(m_topLeft.x) + " " + std::to_string(m_topLeft.y) + " "
			+ std::to_string(m_width) + " " + std::to_string(m_height);
	};

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_topLeft.x, m_topLeft.y, m_topLeft.x + m_width, m_topLeft.y);
		canvas.DrawLine(m_topLeft.x + m_width, m_topLeft.y, m_topLeft.x + m_width, m_topLeft.y - m_height);
		canvas.DrawLine(m_topLeft.x + m_width, m_topLeft.y - m_height, m_topLeft.x, m_topLeft.y - m_height);
		canvas.DrawLine(m_topLeft.x, m_topLeft.y - m_height, m_topLeft.x, m_topLeft.y);
	};

private:
	Point m_topLeft;
	double m_width;
	double m_height;

	void static ValidateCountParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 4)
		{
			throw InvalidCountParametersException();
		}
	};

	void static AssertCorrectRectangleSize(double width, double height)
	{
		if (width <= 0 || height <= 0)
		{
			throw UncorrectRectangleSizeException();
		}
	};
};