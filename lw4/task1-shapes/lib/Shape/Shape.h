#pragma once

#include "../Canvas/Color.h"
#include "../Canvas/ICanvas.h"
#include "./ShapeStrategy/IShapeStrategy.h"
#include <cassert>
#include <memory>
#include <string>

class Shape
{
public:
	Shape(std::unique_ptr<IShapeStrategy> strategy,
		const Color& color)
		: m_strategy(std::move(strategy))
		, m_color(color)
	{
		assert(m_strategy);
	};

	const Color GetColor() const
	{
		return m_color;
	}

	std::string GetDescription() const
	{
		return m_strategy->GetType() + " "
			+ ColorToString(m_color) + " "
			+ m_strategy->GetDescription();
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(m_color);
		m_strategy->Draw(canvas);
	}

	void SetColor(Color color)
	{
		m_color = color;
	}

private:
	Color m_color;
	std::unique_ptr<IShapeStrategy> m_strategy;
};