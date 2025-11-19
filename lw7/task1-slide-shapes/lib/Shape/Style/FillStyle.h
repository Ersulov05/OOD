#pragma once

#include "../../Common/Color.h"
#include "./Style.h"
#include <optional>

class FillStyle : public Style
{
public:
	FillStyle(std::optional<Color> color = std::nullopt)
		: Style(color)
	{
	}
};