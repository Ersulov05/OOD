#pragma once

#include "./IGroupShapes.h"
#include "./IShape.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using GroupShapesList = std::vector<std::unique_ptr<IShape>>;

class GroupShapes : public IGroupShapes
{
public:
	GroupShapes(GroupShapesList shapes)
		: m_shapes(std::move(shapes))
	{
		if (m_shapes.size() < 2)
		{
			throw std::runtime_error("Group consists minimum in 2 shapes");
		}
	}

	Frame GetFrame() const override
	{
		if (m_shapes.empty())
		{
			return { 0, 0, 0, 0 };
		}

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bottom = std::numeric_limits<float>::min();

		for (const auto& shape : m_shapes)
		{
			auto frame = shape->GetFrame();
			left = std::min(left, frame.left);
			right = std::max(right, frame.left + frame.width);
			top = std::min(top, frame.top);
			bottom = std::max(bottom, frame.top + frame.height);
		}

		return { left, top, right - left, bottom - top };
	}

	void SetFrame(const Frame& frame) override
	{
		auto currFrame = GetFrame();
		float widthScale = frame.width / currFrame.width;
		float heightScale = frame.height / currFrame.height;
		float dx = frame.left - currFrame.left;
		float dy = frame.top - currFrame.top;

		for (auto& shape : m_shapes)
		{
			auto shapeCurrFrame = shape->GetFrame();
			auto dxx = shapeCurrFrame.left - currFrame.left;
			auto dyy = shapeCurrFrame.top - currFrame.top;
			shape->SetFrame({
				shapeCurrFrame.left + dx + dxx * widthScale - dxx,
				shapeCurrFrame.top + dy + dyy * heightScale - dyy,
				shapeCurrFrame.width * widthScale,
				shapeCurrFrame.height * heightScale,
			});
		}
	}

	std::optional<Color> GetOutlineColor() const override
	{
		if (m_shapes.empty())
		{
			return std::nullopt;
		}

		auto color = m_shapes.front()->GetOutlineColor();
		for (const auto& shape : m_shapes)
		{
			if (shape->GetOutlineColor() != color)
			{
				return std::nullopt;
			}
		}

		return color;
	}

	void SetOutlineColor(std::optional<Color> color) override
	{
		for (auto& shape : m_shapes)
		{
			shape->SetOutlineColor(color);
		}
	}

	size_t GetOutlineThickness() const override
	{
		if (m_shapes.empty())
		{
			return 0;
		}

		auto thickness = m_shapes.front()->GetOutlineThickness();
		for (const auto& shape : m_shapes)
		{
			if (shape->GetOutlineThickness() != thickness)
			{
				return 0;
			}
		}

		return thickness;
	}

	void SetOutlineThickness(size_t thickness) override
	{
		for (auto& shape : m_shapes)
		{
			shape->SetOutlineThickness(thickness);
		}
	}

	std::optional<Color> GetFillColor() const override
	{
		if (m_shapes.empty())
		{
			return std::nullopt;
		}

		auto color = m_shapes.front()->GetFillColor();
		for (const auto& shape : m_shapes)
		{
			if (shape->GetFillColor() != color)
			{
				return std::nullopt;
			}
		}

		return color;
	}

	void SetFillColor(std::optional<Color> color) override
	{
		for (auto& shape : m_shapes)
		{
			shape->SetFillColor(color);
		}
	}

	std::string GetType() const override
	{
		return "group";
	}

	void AddShape(std::unique_ptr<IShape> shape) override
	{
		m_shapes.push_back(std::move(shape));
	}

	void DeleteShapeByIndex(size_t index)
	{
		if (m_shapes.size() == 2)
		{
			throw std::runtime_error("Group consists minimum in 2 shapes");
		}
		AssertIndexDontOutOfRange(index);
		m_shapes.erase(m_shapes.begin() + index);
	}

	void GroupShapesByIndexes(std::vector<size_t> indexes) override
	{
		ValidateGroupedIndexes(indexes);

		std::sort(indexes.begin(), indexes.end(), std::greater<size_t>());
		GroupShapesList shapesToGroup;
		for (auto index : indexes)
		{
			shapesToGroup.push_back(std::move(m_shapes[index]));
			m_shapes.erase(m_shapes.begin() + index);
		}

		std::reverse(shapesToGroup.begin(), shapesToGroup.end());
		auto group = std::make_unique<GroupShapes>(std::move(shapesToGroup));
		AddShape(std::move(group));
	}

	IShape* GetShapeByIndex(size_t index) override
	{
		AssertIndexDontOutOfRange(index);
		return m_shapes[index].get();
	}

	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void Draw(ICanvas& canvas) const override
	{
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

private:
	GroupShapesList m_shapes;

	void ValidateGroupedIndexes(std::vector<size_t> indexes)
	{
		if (indexes.size() < 2 || m_shapes.size() - indexes.size() < 1)
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
			throw std::invalid_argument("index out of range");
		}
	}
};