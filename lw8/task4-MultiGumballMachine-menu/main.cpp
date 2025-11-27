#include "./lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include "./lib/MenuFP.h"
#include <iostream>

using namespace std;

void RefillGumballMachine(with_dynamic_state::GumballMachine& gumballMachine)
{
	std::cout << "Введите кол-во шариков: ";
	std::string stringNumBalls;
	getline(std::cin, stringNumBalls);
	int numBalls = 0;
	try
	{
		int numBalls = std::stoi(stringNumBalls);
		if (numBalls < 0)
		{
			std::cout << "Invalid count numBalls" << std::endl;
			return;
		}
	}
	catch (std::exception&)
	{
		std::cout << "Invalid count numBalls" << std::endl;
		return;
	}
	gumballMachine.Refill(numBalls);
}

void InfoGumballMachine(with_dynamic_state::GumballMachine& gumballMachine)
{
	std::cout << gumballMachine.ToString() << std::endl;
}

void SetupMenu(CMenuFP& menu, with_dynamic_state::GumballMachine& gumballMachine)
{
	menu.AddItem("info", "Gumball machine info", [&] {
		InfoGumballMachine(gumballMachine);
	});
	menu.AddItem("refill", "Refill gumball machine", [&] {
		RefillGumballMachine(gumballMachine);
	});
	menu.AddItem("insert", "Insert quarter",
		std::bind(&with_dynamic_state::GumballMachine::InsertQuarter, &gumballMachine));
	menu.AddItem("eject", "Reject all quarters",
		std::bind(&with_dynamic_state::GumballMachine::EjectQuarter, &gumballMachine));
	menu.AddItem("turn", "Turn crank",
		std::bind(&with_dynamic_state::GumballMachine::TurnCrank, &gumballMachine));
	menu.AddItem("help", "Show instructions",
		std::bind(&CMenuFP::ShowInstructions, &menu));
	menu.AddItem("exit", "Exit from this menu",
		std::bind(&CMenuFP::Exit, &menu));
}

int main()
{
	with_dynamic_state::GumballMachine gumballMachine(5);
	CMenuFP menu;
	SetupMenu(menu, gumballMachine);

	menu.ShowInstructions();
	menu.Run();

	return 0;
}
