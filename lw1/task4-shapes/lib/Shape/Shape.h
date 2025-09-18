#pragma once

#include "../Canvas/ICanvas.h"
#include "../Color/Color.h"
#include "./ShapeStrategy/IShapeStrategy.h"
#include <cassert>
#include <memory>
#include <string>

class Shape
{
public:
	Shape(const std::string& id, const Color& color,
		std::unique_ptr<IShapeStrategy> strategy)
		: m_id(id)
		, m_color(color)
		, m_strategy(std::move(strategy))
	{
		assert(m_strategy);
	};

	const std::string& GetId() const
	{
		return m_id;
	}

	const Color GetColor() const
	{
		return m_color;
	}

	std::string GetDescription() const
	{
		return m_strategy->GetType() + " "
			+ m_id + " "
			+ ColorToString(m_color) + " "
			+ m_strategy->GetDescription();
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(m_color);
		m_strategy->Draw(canvas);
	}

	void SetShapeStrategy(std::unique_ptr<IShapeStrategy>&& shapeStrategy)
	{
		assert(shapeStrategy);
		m_strategy = std::move(shapeStrategy);
	}

	void Move(double dx, double dy)
	{
		m_strategy->MoveShape(dx, dy);
	}

	void SetColor(Color color)
	{
		m_color = color;
	}

private:
	std::string m_id;
	Color m_color;
	std::unique_ptr<IShapeStrategy> m_strategy;
};