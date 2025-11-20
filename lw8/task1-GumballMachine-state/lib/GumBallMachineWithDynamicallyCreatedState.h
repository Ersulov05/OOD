#pragma once
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{

struct IState
{
	virtual void InsertQuarter(std::ostream& out) = 0;
	virtual void EjectQuarter(std::ostream& out) = 0;
	virtual void TurnCrank(std::ostream& out) = 0;
	virtual void Dispense(std::ostream& out) = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

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
			m_gumballMachine.SetNoQuarterState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};

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
		out << "You can't eject, you haven't inserted a quarter yet\n";
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

class HasQuarterState : public IState
{
public:
	HasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter(std::ostream& out) override
	{
		out << "You can't insert another quarter\n";
	}
	void EjectQuarter(std::ostream& out) override
	{
		out << "Quarter returned\n";
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
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
};

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
	std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
			m_count, m_count != 1 ? "s" : "", m_currentState->ToString());
	}

private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			m_out << "A gumball comes rolling out the slot...\n";
			--m_count;
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
	std::unique_ptr<IState> m_currentState;
	std::ostream& m_out;
};

} // namespace with_dynamic_state
