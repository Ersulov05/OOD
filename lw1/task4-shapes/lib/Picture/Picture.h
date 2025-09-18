#pragma once

#include "../Shape/Point.h"
#include "../Shape/Shape.h"
#include "../Shape/ShapeStrategy/IShapeStrategy.h"
#include <map>
#include <string>
#include <vector>

namespace shapes
{
class Picture
{
public:
	void AddShape(std::unique_ptr<Shape> shape)
	{
		auto shapeId = shape->GetId();
		AssertUniqueShapeId(shapeId);

		m_shapes.push_back(std::move(shape));
	}

	void DeleteShape(const std::string& shapeId)
	{
		auto it = std::find_if(m_shapes.begin(), m_shapes.end(),
			[&shapeId](const std::unique_ptr<Shape>& shape) {
				return shape->GetId() == shapeId;
			});

		if (it != m_shapes.end())
		{
			m_shapes.erase(it);
		}
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

	void ChangeShapeStrategy(const std::string& shapeId, std::unique_ptr<IShapeStrategy>&& shapeStrategy)
	{
		auto shape = FindShapeById(shapeId);
		AssertShapeExists(shape, shapeId);

		shape->SetShapeStrategy(std::move(shapeStrategy));
	}

	void ChangeShapeColor(const std::string& shapeId, Color color)
	{
		auto shape = FindShapeById(shapeId);
		AssertShapeExists(shape, shapeId);

		shape->SetColor(color);
	}

	void MovePicture(double dx, double dy)
	{
		for (auto& shape : m_shapes)
		{
			shape->Move(dx, dy);
		}
	}

	void MoveShape(const std::string& shapeId, double dx, double dy)
	{
		auto shape = FindShapeById(shapeId);
		AssertShapeExists(shape, shapeId);

		shape->Move(dx, dy);
	}

	void DrawShape(const std::string& shapeId, gfx::ICanvas& canvas) const
	{
		auto shape = FindShapeById(shapeId);
		AssertShapeExists(shape, shapeId);

		shape->Draw(canvas);
	}

	void DrawPicture(gfx::ICanvas& canvas) const
	{
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

private:
	Shape* FindShapeById(const std::string& shapeId) const
	{
		auto it = std::find_if(m_shapes.begin(), m_shapes.end(),
			[&shapeId](const std::unique_ptr<Shape>& shape) {
				return shape->GetId() == shapeId;
			});

		if (it != m_shapes.end())
		{
			return it->get();
		}

		return nullptr;
	}

	void AssertShapeExists(Shape* shape, const std::string& shapeId) const
	{
		if (!shape)
		{
			throw std::runtime_error("Shape with id \"" + shapeId + "\" not found");
		}
	}

	void AssertUniqueShapeId(const std::string& shapeId) const
	{
		auto shape = FindShapeById(shapeId);
		if (shape)
		{
			throw std::runtime_error("Shape with id \"" + shapeId + "\" already exists");
		}
	}

	std::vector<std::unique_ptr<Shape>> m_shapes;
};
} // namespace shapes