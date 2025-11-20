#pragma once
#include "../IGumballMachine.h"
#include "./IState.h"
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{
class HasQuarterState : public IState
{
public:
	HasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter(std::ostream& out) override
	{
		auto quarterCount = m_gumballMachine.GetQuarterCount();
		if (quarterCount >= 5)
		{
			out << "You can't insert more than 5 quarter\n";
		}
		else
		{
			out << "You inserted a quarter\n";
			m_gumballMachine.SetQuarterCount(++quarterCount);
		}
	}
	void EjectQuarter(std::ostream& out) override
	{
		auto quarterCount = m_gumballMachine.GetQuarterCount();
		out << quarterCount << " quarter(s) returned\n";
		m_gumballMachine.SetQuarterCount(0);
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank(std::ostream& out) override
	{
		out << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}
	void Dispense(std::ostream& out) override
	{
		out << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	IGumballMachine& m_gumballMachine;
};
} // namespace with_dynamic_state
