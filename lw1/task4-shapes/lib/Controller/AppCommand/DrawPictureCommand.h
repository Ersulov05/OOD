#pragma once

#include "./AppCommand.h"

class DrawPictureCommand : public AppCommand
{
public:
	DrawPictureCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		picture.DrawPicture(canvas);
		canvas.RunWindow();
		// output << "Draw picture" << std::endl;
	}
};
