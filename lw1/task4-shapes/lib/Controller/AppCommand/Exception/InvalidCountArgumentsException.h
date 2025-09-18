#pragma once
#include <iostream>

class InvalidCountArgumentsException : public std::invalid_argument
{
public:
	InvalidCountArgumentsException()
		: std::invalid_argument("Invalid count arguments"){};
};