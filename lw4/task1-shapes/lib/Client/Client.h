#pragma once

#include "../Canvas/CCanvas.h"
#include "../Canvas/ICanvas.h"
#include "../Designer/IDesigner.h"
#include "../Painter/Painter.h"
#include <iostream>

class Client
{
public:
	Client(IDesigner& designer)
		: m_designer(designer)
		, m_canvas(CCanvas(CANVAS_WIDTH, CANVAS_HEIGHT))
	{
	}

	void Handle(std::istream& input, Painter& painter)
	{
		auto pictureDraft = m_designer.CreateDraft(input);
		painter.DrawPicture(pictureDraft, m_canvas);

		m_canvas.RunWindow();
	}

private:
	static constexpr const u_int32_t CANVAS_WIDTH = 800;
	static constexpr const u_int32_t CANVAS_HEIGHT = 600;
	IDesigner& m_designer;
	CCanvas m_canvas;
};