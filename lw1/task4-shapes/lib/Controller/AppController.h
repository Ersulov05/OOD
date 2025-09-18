#pragma once

#include "../Canvas/CCanvas.h"
#include "../Picture/Picture.h"
#include "./AppCommand/Factory/AppCommandFactory.h"
#include "./ConsoleCommand/ConsoleCommand.h"
#include <string>

class AppController
{
public:
	void Run()
	{
		while (true)
		{
			std::cout << "> ";
			auto consoleCommand = GetConsoleCommand(std::cin);
			if (consoleCommand.name == EXIT_COMMAND_NAME)
			{
				break;
			}
			if (consoleCommand.name == EMPTY_COMMAND_NAME)
			{
				continue;
			}

			HandleConsoleCommand(consoleCommand);
		}
	}

private:
	AppCommandFactory m_appCommandFactory;
	Picture m_picture;
	static constexpr const u_int32_t CANVAS_WIDTH = 800;
	static constexpr const u_int32_t CANVAS_HEIGHT = 600;
	CCanvas m_canvas = CCanvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	static constexpr const std::string EXIT_COMMAND_NAME = "exit";
	static constexpr const std::string EMPTY_COMMAND_NAME = "";

	void HandleConsoleCommand(const ConsoleCommand& consoleCommand)
	{
		try
		{
			auto command = m_appCommandFactory.CreateAppCommand(consoleCommand.name, consoleCommand.params);
			command->Execute(std::cout, m_picture, m_canvas);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
};