#pragma once

#include "../../Color/Color.h"
#include "./AppCommand.h"

namespace app
{
class ChangeShapeColorCommand : public AppCommand
{
public:
	ChangeShapeColorCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 1);
		auto shapeId = m_parameters[0];
		auto color = StringToColor(m_parameters[1]);

		picture.ChangeShapeColor(shapeId, color);
		output << "Change shape color" << std::endl;
	}
};
} // namespace app
