#pragma once

#include "../Shape/GroupShapes.h"
#include "../Shape/IShape.h"
#include "./ISlide.h"
#include <memory>

class Slide : public ISlide
{
public:
	Slide(size_t width, size_t height)
		: m_width(width)
		, m_height(height)
	{
	}

	size_t GetHeight() const override
	{
		return m_height;
	}

	size_t GetWidth() const override
	{
		return m_width;
	}

	void AddShape(std::unique_ptr<IShape> shape) override
	{
		m_shapes.push_back(std::move(shape));
	}

	void DeleteShapeByIndex(size_t index) override
	{
		AssertIndexDontOutOfRange(index);
		m_shapes.erase(m_shapes.begin() + index);
	}

	void GroupShapesByIndexes(std::vector<size_t> indexes) override
	{
		ValidateGroupedIndexes(indexes);

		std::sort(indexes.begin(), indexes.end(), std::greater<size_t>());
		std::vector<std::unique_ptr<IShape>> shapesToGroup;
		for (auto index : indexes)
		{
			shapesToGroup.push_back(std::move(m_shapes[index]));
			m_shapes.erase(m_shapes.begin() + index);
		}

		std::reverse(shapesToGroup.begin(), shapesToGroup.end());
		auto group = std::make_unique<GroupShapes>(std::move(shapesToGroup));
		AddShape(std::move(group));
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetWidth(m_width);
		canvas.SetHeight(m_height);
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	IShape* GetShapeByIndex(size_t index) override
	{
		AssertIndexDontOutOfRange(index);
		return m_shapes[index].get();
	}

private:
	size_t m_width;
	size_t m_height;
	std::vector<std::unique_ptr<IShape>> m_shapes;

	void ValidateGroupedIndexes(std::vector<size_t> indexes)
	{
		if (indexes.size() < 2)
		{
			throw std::runtime_error("Invalid grouping operation");
		}

		for (auto index : indexes)
		{
			AssertIndexDontOutOfRange(index);
		}

		auto sorted = indexes;
		std::sort(sorted.begin(), sorted.end());
		if (std::unique(sorted.begin(), sorted.end()) != sorted.end())
		{
			throw std::invalid_argument("Duplicate indexes found");
		}
	}

	void AssertIndexDontOutOfRange(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw std::runtime_error("index out of range");
		}
	}
};