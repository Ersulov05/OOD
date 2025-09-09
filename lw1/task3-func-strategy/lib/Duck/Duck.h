#ifndef DUCK_H
#define DUCK_H

#include "Dance/DanceBehavior.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
	Duck(FlyBehavior flyBehavior,
		QuackBehavior quackBehavior,
		DanceBehavior danceBehavior)
		: m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack() const
	{
		if (m_quackBehavior.isQuackable())
		{
			m_quackBehavior.quack();
		}
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		if (!m_flyBehavior.isFlyable())
			return;

		std::cout << "Вылет номер " << m_flyBehavior.getFlyCounter() + 1 << std::endl;
		m_flyBehavior.fly();
		if (m_flyBehavior.getFlyCounter() % 2 == 0)
		{
			Quack();
		}
	}

	virtual void Dance()
	{
		m_danceBehavior.dance();
	}

	void SetFlyBehavior(FlyBehavior flyBehavior)
	{
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

#endif
