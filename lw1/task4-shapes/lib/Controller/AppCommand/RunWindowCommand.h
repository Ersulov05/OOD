#pragma once

#include "./AppCommand.h"

namespace app
{
class RunWindowCommand : public AppCommand
{
public:
	RunWindowCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) override
	{
		canvas.RunWindow();
	}
};
} // namespace app
