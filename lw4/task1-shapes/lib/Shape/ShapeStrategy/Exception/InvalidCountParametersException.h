#pragma once
#include <iostream>

class InvalidCountParametersException : public std::invalid_argument
{
public:
	InvalidCountParametersException()
		: std::invalid_argument("Invalid count arguments"){};
};