#ifndef MINUETDANCEBEHAVIOR_H
#define MINUETDANCEBEHAVIOR_H

#include "IDanceBehavior.h"
#include <iostream>

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void const Dance() override
	{
		std::cout << "I'm dance minuet!!" << std::endl;
	}
};

#endif
