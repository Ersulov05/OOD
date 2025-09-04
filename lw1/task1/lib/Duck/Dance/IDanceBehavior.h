#ifndef LAB01_SIMUDUCK_IDANCEBEHAVIOR_H
#define LAB01_SIMUDUCK_IDANCEBEHAVIOR_H

struct IDanceBehavior
{
	virtual ~IDanceBehavior(){};
	virtual const void Dance() = 0;
};

#endif
