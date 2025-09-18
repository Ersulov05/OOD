#pragma once

#include "../../Canvas/CCanvas.h"
#include "../../Picture/Picture.h"
#include <iostream>

class IAppCommand
{
public:
	virtual ~IAppCommand() = default;
	virtual void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) = 0;
};
