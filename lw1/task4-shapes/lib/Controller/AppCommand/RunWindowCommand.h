#pragma once

#include "./AppCommand.h"

class RunWindowCommand : public AppCommand
{
public:
	RunWindowCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		canvas.RunWindow();
	}
};
