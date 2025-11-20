#pragma once
#include "../IGumballMachine.h"
#include "./IState.h"
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{
class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter(std::ostream& out) override
	{
		out << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter(std::ostream& out) override
	{
		auto quarterCount = m_gumballMachine.GetQuarterCount();
		out << quarterCount << " quarter(s) returned\n";
		m_gumballMachine.SetQuarterCount(0);
	}
	void TurnCrank(std::ostream& out) override
	{
		out << "You turned but there's no gumballs\n";
	}
	void Dispense(std::ostream& out) override
	{
		out << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
};
} // namespace with_dynamic_state
