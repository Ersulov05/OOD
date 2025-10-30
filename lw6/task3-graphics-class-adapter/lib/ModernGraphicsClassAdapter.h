#pragma once
#include "./graphics_lib.h"
#include "./modern_graphics_lib.h"
#include <cstdint>

class ModernGraphicsClassAdapter
	: public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsClassAdapter(std::ostream& out)
		: CModernGraphicsRenderer(out)
		, m_start(0, 0)
	{
	}

	void SetColor(uint32_t color) override
	{
		m_color = color;
	}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(const int x, const int y) override
	{
		const modern_graphics_lib::CPoint end(x, y);

		DrawLine(m_start, end, convertColorToRGBAColor(m_color));
		MoveTo(x, y);
	}

	void BeginDraw()
	{
		CModernGraphicsRenderer::BeginDraw();
	}

	void EndDraw()
	{
		CModernGraphicsRenderer::EndDraw();
	}

private:
	modern_graphics_lib::CPoint m_start;
	uint32_t m_color = 0;

	modern_graphics_lib::CRGBAColor convertColorToRGBAColor(uint32_t color)
	{
		float r = (float)((color >> 16) & 0xFF) / 255;
		float g = (float)((color >> 8) & 0xFF) / 255;
		float b = (float)(color & 0xFF) / 255;
		float a = (float)((color >> 24) & 0xFF) / 255;

		return modern_graphics_lib::CRGBAColor(r, g, b, a);
	}
};