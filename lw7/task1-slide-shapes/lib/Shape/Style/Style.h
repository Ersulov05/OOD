#pragma once

#include "../../Common/Color.h"
#include <optional>

class Style
{
public:
	Style(std::optional<Color> color = std::nullopt)
		: m_color(color)
	{
	}

	void SetColor(std::optional<Color> color)
	{
		m_color = color;
	}

	std::optional<Color> GetColor() const
	{
		return m_color;
	}

private:
	std::optional<Color> m_color;
};