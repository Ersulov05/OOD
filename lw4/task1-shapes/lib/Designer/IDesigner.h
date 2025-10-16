#pragma once

#include "../PictureDraft/PictureDraft.h"
#include <iostream>

class IDesigner
{
public:
	virtual ~IDesigner() = default;
	virtual PictureDraft CreateDraft(std::istream& input) = 0;
};
