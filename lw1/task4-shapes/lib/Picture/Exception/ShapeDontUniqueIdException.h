#pragma once
#include <iostream>

class ShapeDontUniqueIdException : public std::invalid_argument
{
public:
	ShapeDontUniqueIdException(const std::string& shapeId)
		: std::invalid_argument("Shape with id \"" + shapeId + "\" already exists"){};
};