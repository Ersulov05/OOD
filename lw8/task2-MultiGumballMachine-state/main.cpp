#include "./lib/GamballMachineDinamical/MultiGumBallMachine.h"
#include "./lib/MultiNaiveMultiGumBallMachine.h"

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& m)
{
	cout << m.ToString() << endl;

	// m.InsertQuarter();
	// m.TurnCrank();

	// cout << m.ToString() << endl;

	// m.InsertQuarter();
	// m.EjectQuarter();
	// m.TurnCrank();

	// cout << m.ToString() << endl;

	// m.InsertQuarter();
	// m.TurnCrank();
	// m.InsertQuarter();
	// m.TurnCrank();
	// m.EjectQuarter();

	// cout << m.ToString() << endl;

	// m.InsertQuarter();
	// m.InsertQuarter();
	// m.TurnCrank();
	// m.InsertQuarter();
	// m.TurnCrank();
	// m.InsertQuarter();
	// m.TurnCrank();

	// cout << m.ToString() << endl;

	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;

	m.TurnCrank();
	cout << m.ToString() << endl;
	m.TurnCrank();
	cout << m.ToString() << endl;
	m.TurnCrank();
	cout << m.ToString() << endl;
	m.TurnCrank();
	cout << m.ToString() << endl;
	m.TurnCrank();
	cout << m.ToString() << endl;

	m.TurnCrank();
	cout << m.ToString() << endl;
	m.InsertQuarter();
	cout << m.ToString() << endl;
	m.EjectQuarter();

	cout << m.ToString() << endl;
}

void TestNaiveGumballMachine()
{
	naive::GumballMachine m(5);
	TestGumballMachine(m);
}

void TestGumballMachineWithDynamicState()
{
	with_dynamic_state::GumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{
	cout << "\n-----------------\n";
	TestNaiveGumballMachine();

	return 0;
}
