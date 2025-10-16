#pragma once

#include "../Shape.h"
#include <string>

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::unique_ptr<Shape> CreateShape(const std::vector<std::string>& params) = 0;
};
