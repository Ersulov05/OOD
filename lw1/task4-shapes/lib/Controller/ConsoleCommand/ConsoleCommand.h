#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace app
{
struct ConsoleCommand
{
	std::string name;
	std::vector<std::string> params;
};

void GetStringArgs(std::istream& lineStream, std::vector<std::string>& stringArgs)
{
	std::string arg;
	while (lineStream >> arg)
	{
		stringArgs.push_back(arg);
	}
}

ConsoleCommand GetConsoleCommand(std::istream& input)
{
	std::string line;
	getline(input, line);

	std::istringstream lineStream(line);
	ConsoleCommand command;

	lineStream >> command.name;
	GetStringArgs(lineStream, command.params);

	return command;
}
} // namespace app