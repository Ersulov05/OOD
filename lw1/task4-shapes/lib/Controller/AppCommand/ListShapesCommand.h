#pragma once

#include "./AppCommand.h"

namespace app
{
class ListShapesCommand : public AppCommand
{
public:
	ListShapesCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) override
	{
		auto shapes = picture.ListShapes();
		int num = 1;
		for (auto const& shape : shapes)
		{
			output << num << " " << shape->GetDescription() << std::endl;
		}
	}
};
} // namespace app
