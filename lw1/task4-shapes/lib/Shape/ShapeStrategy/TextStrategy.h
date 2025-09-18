#pragma once

#include "../Point.h"
#include "./IShapeStrategy.h"

class TextStrategy : public shapes::IShapeStrategy
{
public:
	TextStrategy(const std::vector<std::string>& parametrs)
	{
		ValidateParameters(parametrs);

		m_topLeft = Point(std::stod(parametrs[0]), std::stod(parametrs[1]));
		m_size = std::stod(parametrs[2]);
		m_text = parametrs[3];
	};

	std::string GetType() const override
	{
		return "text";
	}

	std::string GetDescription() const override
	{
		return "text description";
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

	void static ValidateParameters(const std::vector<std::string>& parameters)
	{
		if (parameters.size() != 4)
		{
			throw std::invalid_argument("Invalid count arguments");
		}
	};
};