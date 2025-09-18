#pragma once

#include "../Point.h"
#include "./Exception/InvalidCountParametersException.h"
#include "./IShapeStrategy.h"

class TextStrategy : public shapes::IShapeStrategy
{
public:
	TextStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateCountParameters(parametrs);

		m_topLeft = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_size = std::stod(parametrs[2]);
		m_text = parametrs[3];
		for (auto param = parametrs.begin() + 4; param != parametrs.end(); ++param)
		{
			m_text += " " + *param;
		}
	};

	std::string GetType() const override
	{
		return "text";
	}

	std::string GetDescription() const override
	{
		return std::to_string(m_topLeft.x) + " " + std::to_string(m_topLeft.y) + " "
			+ std::to_string(m_size) + " " + m_text;
	};

	void Draw(gfx::ICanvas& canvas) const override
	{
		canvas.DrawText(m_topLeft.x, m_topLeft.y, m_size, m_text);
	};

	void MoveShape(double dx, double dy) override
	{
		m_topLeft.x += dx;
		m_topLeft.y += dy;
	}

private:
	Point m_topLeft;
	std::string m_text;
	u_int32_t m_size;

	void static ValidateCountParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() < 4)
		{
			throw InvalidCountParametersException();
		}
	};
};