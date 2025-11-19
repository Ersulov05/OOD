#pragma once

#include "../Common/Color.h"
#include "../Common/Frame.h"
#include "./IDrawable.h"
#include <optional>

class IShape : public IDrawable
{
public:
	virtual std::string GetType() const = 0;

	virtual Frame GetFrame() const = 0;

	virtual void SetFrame(const Frame& frame) = 0;

	virtual std::optional<Color> GetOutlineColor() const = 0;

	virtual void SetOutlineColor(std::optional<Color> color) = 0;

	virtual size_t GetOutlineThickness() const = 0;

	virtual void SetOutlineThickness(size_t thickness) = 0;

	virtual std::optional<Color> GetFillColor() const = 0;

	virtual void SetFillColor(std::optional<Color> color) = 0;

	~IShape() override = default;
};