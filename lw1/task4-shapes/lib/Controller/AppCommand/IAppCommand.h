#pragma once

#include "../../Canvas/CCanvas.h"
#include "../../Picture/Picture.h"
#include <iostream>

namespace app
{
class IAppCommand
{
public:
	virtual ~IAppCommand() = default;
	virtual void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) = 0;
};
} // namespace app
