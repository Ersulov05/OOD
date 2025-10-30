#pragma once
#include "./graphics_lib.h"
#include "./modern_graphics_lib.h"

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

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);

		DrawLine(m_start, end);
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
};