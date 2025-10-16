#pragma once
#include <iostream>

class UncorrectCircleRadiusException : public std::invalid_argument
{
public:
	UncorrectCircleRadiusException()
		: std::invalid_argument("Uncorrect circle radius"){};
};