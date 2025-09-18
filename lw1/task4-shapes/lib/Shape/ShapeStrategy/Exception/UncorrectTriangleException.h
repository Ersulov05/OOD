#pragma once
#include <iostream>

class UncorrectTriangleException : public std::invalid_argument
{
public:
	UncorrectTriangleException()
		: std::invalid_argument("Uncorrect triangle vertex coords"){};
};