#pragma once
#include "../IGumballMachine.h"
#include "./IState.h"
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{
class NoQuarterState : public IState
{
public:
	NoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter(std::ostream& out) override
	{
		out << "You inserted a quarter\n";
		m_gumballMachine.SetQuarterCount(1);
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter(std::ostream& out) override
	{
		out << "You haven't inserted a quarter\n";
	}
	void TurnCrank(std::ostream& out) override
	{
		out << "You turned but there's no quarter\n";
	}
	void Dispense(std::ostream& out) override
	{
		out << "You need to pay first\n";
	}
	void Refill(unsigned numBalls, std::ostream& out) override
	{
		out << "Refill\n";

		m_gumballMachine.SetBallCount(numBalls);
		if (numBalls == 0)
		{
			m_gumballMachine.SetSoldOutState();
		}
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
};
} // namespace with_dynamic_state
