#pragma once
#include "../IGumballMachine.h"
#include "./IState.h"
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{
class SoldState : public IState
{
public:
	SoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter(std::ostream& out) override
	{
		out << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter(std::ostream& out) override
	{
		out << "Sorry you already turned the crank\n";
	}
	void TurnCrank(std::ostream& out) override
	{
		out << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense(std::ostream& out) override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			out << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}
	}
	void Refill(unsigned numBalls, std::ostream& out) override
	{
		out << "Please wait, we're already giving you a gumball\n";
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};
} // namespace with_dynamic_state
