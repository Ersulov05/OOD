#pragma once

#include "./AppCommand.h"

class MovePictureCommand : public AppCommand
{
public:
	MovePictureCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 2);

		auto dx = std::stod(m_parameters[0]);
		auto dy = std::stod(m_parameters[1]);

		picture.MovePicture(dx, dy);
		output << "Move picture" << std::endl;
	}
};
