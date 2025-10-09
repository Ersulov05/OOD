#pragma once
#include <iostream>
#include <string>

class EnoughtCountArgumentsException : public std::invalid_argument
{
public:
	EnoughtCountArgumentsException(const std::string& optionName)
		: std::invalid_argument("Enought count arguments for option " + optionName){};
};