#pragma once

#include "../Shape/IDrawable.h"
#include <memory>

class ISlide : public IDrawable
{
	virtual size_t GetHeight() const = 0;
	virtual size_t GetWidth() const = 0;
	virtual void AddShape(std::unique_ptr<IShape> shape) = 0;
	virtual void DeleteShapeByIndex(size_t index) = 0;
	virtual void GroupShapesByIndexes(std::vector<size_t> indexes) = 0;
	virtual IShape* GetShapeByIndex(size_t index) = 0;
};