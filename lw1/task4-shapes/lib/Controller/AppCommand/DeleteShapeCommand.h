#pragma once

#include "./AppCommand.h"

class DeleteShapeCommand : public AppCommand
{
public:
	DeleteShapeCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 1);

		auto shapeId = m_parameters[0];

		picture.DeleteShape(shapeId);
	}
};
