#pragma once

#include "./QuackBehavior.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

QuackBehavior createMuteQuackBehavior()
{
	return QuackBehavior{
		[]() {},
		[]() { return false; }
	};
}

QuackBehavior createQuackBehavior()
{
	return QuackBehavior{
		[]() {
			std::cout << "Quack Quack!!!" << std::endl;
		},
		[]() { return true; }
	};
}

QuackBehavior createSqueakQuackBehavior()
{
	return QuackBehavior{
		[]() {
			std::cout << "Squeek!!!" << std::endl;
		},
		[]() { return true; }
	};
}
