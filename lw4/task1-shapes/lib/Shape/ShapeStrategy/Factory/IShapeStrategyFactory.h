#pragma once

#include "../IShapeStrategy.h"
#include <string>

class IShapeStrategyFactory
{
public:
	virtual ~IShapeStrategyFactory() = default;
	virtual std::unique_ptr<IShapeStrategy> CreateShapeStrategy(const std::string& type, const std::vector<std::string>& params = {}) const = 0;
};
