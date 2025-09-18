#pragma once

#include "../../Canvas/CCanvas.h"
#include "./Exception/InvalidCountArgumentsException.h"
#include "./IAppCommand.h"
#include <string>
#include <vector>

class AppCommand : public IAppCommand
{
public:
	AppCommand(const std::vector<std::string>& parameters)
		: m_parameters(parameters)
	{
	}

	virtual void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
	}

protected:
	std::vector<std::string> m_parameters;

	void static AssertCorrectCountArguments(int countArguments, int expected)
	{
		if (countArguments < expected)
		{
			throw InvalidCountArgumentsException();
		}
	}
};
