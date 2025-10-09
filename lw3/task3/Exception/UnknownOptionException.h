#pragma once
#include <iostream>
#include <string>

class UnknownOptionException : public std::invalid_argument
{
public:
	UnknownOptionException(const std::string& optionName)
		: std::invalid_argument("Unknown option " + optionName){};
};