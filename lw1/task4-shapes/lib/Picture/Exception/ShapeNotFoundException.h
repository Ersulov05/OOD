#pragma once
#include <iostream>

class ShapeNotFoundException : public std::invalid_argument
{
public:
	ShapeNotFoundException(const std::string& shapeId)
		: std::invalid_argument("Shape with id \"" + shapeId + "\" not found"){};
};