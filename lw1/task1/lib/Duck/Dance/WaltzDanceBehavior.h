#ifndef WALTZDANCEBEHAVIOR_H
#define WALTZDANCEBEHAVIOR_H

#include "IDanceBehavior.h"
#include <iostream>

class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "I'm dance waltz!!" << std::endl;
	}
};

#endif
