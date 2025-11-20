#pragma once
#include <iostream>
#include <string>

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
} // namespace with_dynamic_state
