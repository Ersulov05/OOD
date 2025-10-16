#pragma once
#include <iostream>

class UnknownColorException : public std::invalid_argument
{
public:
	UnknownColorException()
		: std::invalid_argument("Unknown color when converting in SFMLColor"){};
};