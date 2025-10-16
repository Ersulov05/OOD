#pragma once

#include "../Canvas/ICanvas.h"
#include "../PictureDraft/PictureDraft.h"

class Painter
{
public:
	void DrawPicture(const PictureDraft& pictureDraft, ICanvas& canvas)
	{
		auto shapes = pictureDraft.ListShapes();
		for (const auto& shape : shapes)
		{
			shape->Draw(canvas);
		}
	}
};
