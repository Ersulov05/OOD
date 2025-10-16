#pragma once
#include <iostream>
#include <string>

class UnknownShapeTypeException : public std::invalid_argument
{
public:
	UnknownShapeTypeException(const std::string& type)
		: std::invalid_argument("Unknown shape type '" + type + "'"){};
};