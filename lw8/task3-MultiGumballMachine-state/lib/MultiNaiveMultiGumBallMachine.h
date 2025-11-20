#pragma once

#include <format>
#include <iostream>

namespace naive
{
class GumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	GumballMachine(unsigned count, std::ostream& out = std::cout)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		, m_out(out)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			m_out << "You inserted a quarter\n";
			m_quarterCount = 1;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarterCount >= 5)
			{
				m_out << "You can't insert more than 5 quarter\n";
			}
			else
			{
				m_out << "You inserted a quarter\n";
				++m_quarterCount;
			}
			break;
		case State::Sold:
			m_out << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			m_out << m_quarterCount << " quarter(s) returned\n";
			m_quarterCount = 0;
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			m_out << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_out << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			m_out << m_quarterCount << " quarter(s) returned\n";
			m_quarterCount = 0;
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			m_out << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			m_out << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			m_out << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0
			? m_quarterCount > 0
				? State::NoQuarter
				: State::HasQuarter
			: State::SoldOut;
	}

	std::string ToString() const
	{
		return std::format(
			"Mighty Gumball, Inc.\n"
			"C++-enabled Standing Gumball Model #2016\n"
			"Inventory: {} gumball{}; {} quarter{}\n"
			"Machine is {}\n",
			m_count,
			m_count != 1 ? "s" : "",
			m_quarterCount,
			m_quarterCount != 1 ? "s" : "",
			GetState());

		std::string state = GetState();
	}

	std::string GetState() const
	{
		return (m_state == State::SoldOut)
			? "sold out"
			: (m_state == State::NoQuarter)	 ? "waiting for quarter"
			: (m_state == State::HasQuarter) ? "waiting for turn of crank"
											 : "delivering a gumball";
		;
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			m_out << "A gumball comes rolling out the slot\n";
			--m_count;
			--m_quarterCount;
			if (m_count == 0)
			{
				m_out << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				if (m_quarterCount == 0)
				{
					m_state = State::NoQuarter;
				}
				else
				{
					m_state = State::HasQuarter;
				}
			}
			break;
		case State::NoQuarter:
			m_out << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			m_out << "No gumball dispensed\n";
			break;
		}
	}

	unsigned m_count; // Количество шариков
	unsigned m_quarterCount = 0;
	State m_state = State::SoldOut;
	std::ostream& m_out;
};
} // namespace naive