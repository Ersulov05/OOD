#ifndef WALTZDANCEBEHAVIOR_H
#define WALTZDANCEBEHAVIOR_H

#include "IDanceBehavior.h"
#include <iostream>

class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void const Dance() override
	{
		std::cout << "I'm dance waltz!!" << std::endl;
	}
};

#endif
