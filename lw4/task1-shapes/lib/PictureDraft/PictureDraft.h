#pragma once

#include "../Shape/Shape.h"
#include <map>
#include <vector>

class PictureDraft
{
public:
	void AddShape(std::unique_ptr<Shape> shape)
	{
		m_shapes.push_back(std::move(shape));
	}

	const std::vector<std::shared_ptr<const Shape>> ListShapes() const
	{
		std::vector<std::shared_ptr<const Shape>> result;
		for (const auto& shape : m_shapes)
		{
			result.push_back(std::shared_ptr<const Shape>(shape.get(), [](auto*) {}));
		}

		return result;
	}

private:
	std::vector<std::unique_ptr<Shape>> m_shapes;
};