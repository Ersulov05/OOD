#include "./lib/MenuFP.h"
#include "./lib/Robot.h"

std::vector<std::string> GetCommandNames(CMenuFP& menu)
{
	std::vector<std::string> commandNames;
	std::string command;
	while (true)
	{
		std::cout << "+> ";
		std::getline(std::cin, command);
		if (command == "end_macro")
		{
			break;
		}

		if (menu.AreCommandExists(command))
		{
			commandNames.push_back(command);
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	}

	return commandNames;
}

void AddMacroCommand(CMenuFP& menu)
{
	std::string shortcut, description;
	std::cout << "Введите название команды: " << std::endl;
	std::getline(std::cin, shortcut);
	if (menu.AreCommandExists(shortcut))
	{
		std::cout << "Command already exists" << std::endl;
		std::cout << "Запись макрокоманды отменена" << std::endl;
		return;
	}

	std::cout << "Введите описание команды: " << std::endl;
	std::getline(std::cin, description);
	std::cout << "Запись макрокоманды началась" << std::endl;
	std::cout << "Для завершения введите end_macro" << std::endl;

	auto commandNames = GetCommandNames(menu);
	menu.AddMacroCommand(shortcut, description, commandNames);
	std::cout << "Макрокоманда записана" << std::endl;
}

void SetupMenu(CMenuFP& menu, Robot& robot)
{
	menu.AddItem("on", "Turns the Robot on", [&] {
		robot.TurnOn();
	});
	menu.AddItem("off", "Turns the Robot off",
		std::bind(&Robot::TurnOff, &robot));
	menu.AddItem("north", "Makes the Robot walk north",
		std::bind(&Robot::Walk, &robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
		std::bind(&Robot::Walk, &robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
		std::bind(&Robot::Walk, &robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
		std::bind(&Robot::Walk, &robot, WalkDirection::East));
	menu.AddItem("stop", "Stops the Robot",
		std::bind(&Robot::Stop, &robot));
	menu.AddItem("begin_macro", "Begin recording macro command", [&] {
		AddMacroCommand(menu);
	});
	menu.AddItem("help", "Show instructions",
		std::bind(&CMenuFP::ShowInstructions, &menu));
	menu.AddItem("exit", "Exit from this menu",
		std::bind(&CMenuFP::Exit, &menu));
}

int main()
{
	Robot robot;
	CMenuFP menu;

	SetupMenu(menu, robot);
	menu.ShowInstructions();
	menu.Run();

	return 0;
}