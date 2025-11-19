#pragma once

#include "./IShape.h"
#include <vector>

class IGroupShapes : public IShape
{
	virtual void AddShape(std::unique_ptr<IShape> shape) = 0;
	virtual void DeleteShapeByIndex(size_t index) = 0;
	virtual void GroupShapesByIndexes(std::vector<size_t> indexes) = 0;
	virtual IShape* GetShapeByIndex(size_t index) = 0;
	virtual size_t GetShapesCount() const = 0;
};