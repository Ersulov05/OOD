#pragma once

#include "../../Canvas/ICanvas.h"
#include <string>
#include <vector>

namespace shapes
{
class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() = default;
	virtual std::string GetType() const = 0;
	virtual std::string GetDescription() const = 0;
	virtual void Draw(gfx::ICanvas& canvas) const = 0;
	virtual void MoveShape(double dx, double dy) = 0;
};
}