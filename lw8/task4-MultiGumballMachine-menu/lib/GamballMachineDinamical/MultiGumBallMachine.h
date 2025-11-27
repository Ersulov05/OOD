#pragma once
#include "./IGumballMachine.h"
#include "./State/HasQuarterState.h"
#include "./State/IState.h"
#include "./State/NoQuarterState.h"
#include "./State/SoldOutState.h"
#include "./State/SoldState.h"
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{
class GumballMachine : public IGumballMachine
{
public:
	GumballMachine(unsigned numBalls, std::ostream& out = std::cout)
		: m_count(numBalls)
		, m_out(out)
	{
		if (m_count > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}
	void EjectQuarter()
	{
		m_currentState->EjectQuarter(m_out);
	}
	void InsertQuarter()
	{
		m_currentState->InsertQuarter(m_out);
	}
	void TurnCrank()
	{
		m_currentState->TurnCrank(m_out);
		m_currentState->Dispense(m_out);
	}
	void Refill(unsigned numBalls)
	{
		m_currentState->Refill(numBalls, m_out);
	}

	std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}; {} quarter{}
Machine is {}
)",
			m_count,
			m_count != 1 ? "s" : "",
			m_quarterCount,
			m_quarterCount != 1 ? "s" : "",
			m_currentState->ToString());
	}

private:
	unsigned GetQuarterCount() const override
	{
		return m_quarterCount;
	}

	void SetQuarterCount(unsigned quarterCount) override
	{
		m_quarterCount = quarterCount;
	}
	void SetBallCount(unsigned numBalls) override
	{
		m_count = numBalls;
	}

	unsigned GetBallCount() const override
	{
		return m_count;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0 && m_quarterCount != 0)
		{
			m_out << "A gumball comes rolling out the slot...\n";
			--m_count;
			--m_quarterCount;
		}
	}

	void SetSoldOutState() override
	{
		m_currentState.reset(new SoldOutState(*this));
	}
	void SetNoQuarterState() override
	{
		m_currentState.reset(new NoQuarterState(*this));
	}
	void SetSoldState() override
	{
		m_currentState.reset(new SoldState(*this));
	}
	void SetHasQuarterState() override
	{
		m_currentState.reset(new HasQuarterState(*this));
	}

private:
	unsigned m_count = 0;
	unsigned m_quarterCount = 0;
	std::unique_ptr<IState> m_currentState;
	std::ostream& m_out;
};

} // namespace with_dynamic_state
