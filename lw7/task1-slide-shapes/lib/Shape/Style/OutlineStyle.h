#pragma once

#include "../../Common/Color.h"
#include "./Style.h"
#include <optional>

class OutlineStyle : public Style
{
public:
	OutlineStyle(std::optional<Color> color = std::nullopt, size_t thickness = 1)
		: Style(color)
		, m_thickness(thickness)
	{
	}

	void SetThickness(size_t thickness)
	{
		m_thickness = thickness;
	}

	size_t GetThickness() const
	{
		return m_thickness;
	}

private:
	size_t m_thickness;
};