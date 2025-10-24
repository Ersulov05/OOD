#include "./lib/Commands.h"
#include "./lib/MenuFP.h"

using namespace std;

void AddMacroCommand(CMenuFP& menu)
{
	std::string shortcut, description;
	std::vector<std::string> commandNames;

	std::cout << "Введите название команды: " << std::endl;
	std::getline(std::cin, shortcut);

	std::cout << "Введите описание команды: " << std::endl;
	std::getline(std::cin, description);

	std::string command;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, command);
		if (command == "end_macro")
		{
			break;
		}

		if (menu.IsCommandExists(command))
		{
			commandNames.push_back(command);
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	}

	menu.AddMacroCommand(shortcut, description, commandNames);
	std::cout << "Макрокоманда записана" << std::endl;
}

void SetupMenu(CMenuFP& menu, Robot& robot)
{
	menu.AddItem("on", "Turns the Robot on", [&] {
		robot.TurnOn();
	});
	menu.AddItem("off", "Turns the Robot off",
		bind(&Robot::TurnOff, &robot));

	menu.AddItem("north", "Makes the Robot walk north",
		bind(&Robot::Walk, &robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
		bind(&Robot::Walk, &robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
		bind(&Robot::Walk, &robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
		bind(&Robot::Walk, &robot, WalkDirection::East));

	menu.AddItem("stop", "Stops the Robot",
		bind(&Robot::Stop, &robot));

	// menu.AddItem("patrol", "Patrol the territory", CreateMacroCommand<vector<CMenuFP::Command>>({ bind(&Robot::TurnOn, &robot), bind(&Robot::Walk, &robot, WalkDirection::North), bind(&Robot::Walk, &robot, WalkDirection::South), bind(&Robot::Walk, &robot, WalkDirection::West), bind(&Robot::Walk, &robot, WalkDirection::East), bind(&Robot::TurnOff, &robot) }));

	menu.AddItem("begin_macro", "Start recording a new macro", [&] {
		AddMacroCommand(menu);
	});

	menu.AddItem("help", "Show instructions",
		bind(&CMenuFP::ShowInstructions, &menu));
	menu.AddItem("exit", "Exit from this menu",
		bind(&CMenuFP::Exit, &menu));
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