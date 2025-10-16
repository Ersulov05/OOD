#pragma once

#include "../Point.h"
#include "./Exception/InvalidCountParametersException.h"
#include "./IShapeStrategy.h"

class LineStrategy : public IShapeStrategy
{
public:
	LineStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateCountParameters(parametrs);

		m_start = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_end = Point(std::stod(parametrs[2]), std::stod(parametrs[3]));
	};

	std::string GetType() const override
	{
		return "line";
	}

	std::string GetDescription() const override
	{
		return std::to_string(m_start.y) + " " + std::to_string(m_start.y) + " "
			+ std::to_string(m_end.x) + " " + std::to_string(m_end.y);
	};

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_start.x, m_start.y, m_end.x, m_end.y);
	};

private:
	Point m_start;
	Point m_end;

	void static ValidateCountParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 4)
		{
			throw InvalidCountParametersException();
		}
	};
};