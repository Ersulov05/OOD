#ifndef IQUAKBEHAVIOR_H
#define IQUAKBEHAVIOR_H

struct IQuackBehavior
{
	virtual ~IQuackBehavior(){};
	virtual void Quack() = 0;
	virtual bool isQuackable() const = 0;
};

#endif
