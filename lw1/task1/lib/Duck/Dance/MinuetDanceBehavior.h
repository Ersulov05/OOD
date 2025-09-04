#ifndef MINUETDANCEBEHAVIOR_H
#define MINUETDANCEBEHAVIOR_H

#include "IDanceBehavior.h"
#include <iostream>

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "I'm dance minuet!!" << std::endl;
	}
};

#endif
