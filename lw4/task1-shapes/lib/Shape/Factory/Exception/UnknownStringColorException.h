#pragma once
#include <iostream>
#include <string>

class UnknownStringColorException : public std::invalid_argument
{
public:
	UnknownStringColorException(const std::string& color)
		: std::invalid_argument("Unknown color '" + color + "'"){};
};