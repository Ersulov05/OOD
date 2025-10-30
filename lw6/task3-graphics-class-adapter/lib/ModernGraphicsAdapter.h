#pragma once
#include "./graphics_lib.h"
#include "./modern_graphics_lib.h"
#include <cstdint>

class ModernGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsAdapter(
		modern_graphics_lib::CModernGraphicsRenderer& modernRenderer)
		: m_start(0, 0)
		, m_renderer(modernRenderer)
	{
	}

	void SetColor(uint32_t color) override
	{
		m_color = convertColorToRGBAColor(color);
	}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);

		m_renderer.DrawLine(m_start, end, m_color);
		MoveTo(x, y);
	}

	void BeginDraw()
	{
		m_renderer.BeginDraw();
	}

	void EndDraw()
	{
		m_renderer.EndDraw();
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CRGBAColor m_color{ 0, 0, 0, 0 };
	modern_graphics_lib::CPoint m_start;

	modern_graphics_lib::CRGBAColor convertColorToRGBAColor(uint32_t color)
	{
		float r = (float)((color >> 16) & 0xFF) / 255;
		float g = (float)((color >> 8) & 0xFF) / 255;
		float b = (float)(color & 0xFF) / 255;
		float a = (float)((color >> 24) & 0xFF) / 255;

		return modern_graphics_lib::CRGBAColor(r, g, b, a);
	}
};