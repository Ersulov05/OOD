#pragma once

#include "../Quack/IQuakBehavior.h"
#include <iostream>

class MockQuackBehavior : public IQuackBehavior
{
public:
	MockQuackBehavior(bool quackable = true)
		: m_quackable(quackable)
	{
	}

	void Quack() override
	{
		++m_quackCounter;
	}

	bool IsQuackable() const override
	{
		return m_quackable;
	}

	int GetQuackCounter() const
	{
		return m_quackCounter;
	}

private:
	int m_quackCounter = 0;
	bool m_quackable;
};
