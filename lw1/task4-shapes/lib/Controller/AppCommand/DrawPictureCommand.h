#pragma once

#include "./AppCommand.h"

namespace app
{
class DrawPictureCommand : public AppCommand
{
public:
	DrawPictureCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) override
	{
		picture.DrawPicture(canvas);
		canvas.RunWindow();
		// output << "Draw picture" << std::endl;
	}
};
} // namespace app
