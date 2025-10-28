#pragma once
#include "./graphics_lib.h"
#include "./modern_graphics_lib.h"

class ModernGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsAdapter(
		modern_graphics_lib::CModernGraphicsRenderer& modernRenderer)
		: m_start(0, 0)
		, m_renderer(modernRenderer)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(const int x, const int y) override
	{
		const modern_graphics_lib::CPoint end(x, y);

		m_renderer.DrawLine(m_start, end);

		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CPoint m_start;
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
};