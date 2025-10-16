#pragma once

#include "../../Canvas/ICanvas.h"
#include <string>
#include <vector>

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() = default;
	virtual std::string GetType() const = 0;
	virtual std::string GetDescription() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};