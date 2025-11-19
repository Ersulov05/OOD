#pragma once

#include "./IShape.h"
#include "./Style/FillStyle.h"
#include "./Style/OutlineStyle.h"
#include <memory>

class Shape : public IShape
{
public:
	Shape(const Frame& frame, OutlineStyle lineStyle, FillStyle fillStyle)
		: m_frame(frame)
		, m_lineStyle(std::move(lineStyle))
		, m_fillStyle(std::move(fillStyle))
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		auto fillColor = GetFillColor();
		auto outlineColor = GetOutlineColor();
		size_t thickness = GetOutlineThickness() > 0
			? GetOutlineThickness()
			: 1;
		canvas.SetThickness(GetOutlineThickness());
		canvas.SetFillColor(fillColor);
		canvas.SetOutlineColor(outlineColor);
	}

	Frame GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const Frame& frame) override
	{
		m_frame = frame;
	}

	std::optional<Color> GetOutlineColor() const override
	{
		return m_lineStyle.GetColor();
	}

	void SetOutlineColor(std::optional<Color> color) override
	{
		m_lineStyle.SetColor(color);
	}

	size_t GetOutlineThickness() const override
	{
		return m_lineStyle.GetThickness();
	}

	void SetOutlineThickness(size_t thickness) override
	{
		m_lineStyle.SetThickness(thickness);
	}

	std::optional<Color> GetFillColor() const override
	{
		return m_fillStyle.GetColor();
	};

	virtual void SetFillColor(std::optional<Color> color) override
	{
		m_fillStyle.SetColor(color);
	}

private:
	Frame m_frame;
	OutlineStyle m_lineStyle;
	FillStyle m_fillStyle;
};