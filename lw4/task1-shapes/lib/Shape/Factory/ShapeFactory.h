#pragma once

#include "../../Canvas/Color.h"
#include "../ShapeStrategy/Factory/IShapeStrategyFactory.h"
#include "../ShapeStrategy/Factory/ShapeStrategyFactory.h"
#include "./Exception/UnknownStringColorException.h"
#include "./IShapeFactrory.h"
#include <string>
#include <unordered_map>

class ShapeFactory : public IShapeFactory
{
public:
	ShapeFactory()
		: m_shapeStrategyFactory(std::make_unique<ShapeStrategyFactory>())
	{
	}

	std::unique_ptr<Shape> CreateShape(const std::vector<std::string>& params) override
	{
		Color color = ConvertStringToColor(params[0]);
		std::string type = params[1];
		auto shapeStrategyParams = std::vector<std::string>(params.begin() + 2, params.end());
		auto shapeStrategy = m_shapeStrategyFactory->CreateShapeStrategy(type, shapeStrategyParams);

		return std::make_unique<Shape>(std::move(shapeStrategy), color);
	}

private:
	std::unique_ptr<IShapeStrategyFactory> m_shapeStrategyFactory;

	const std::unordered_map<std::string, Color> colorMap = {
		{ "Red", Color::Red },
		{ "Green", Color::Green },
		{ "Blue", Color::Blue },
		{ "Yellow", Color::Yellow },
		{ "Pink", Color::Pink },
		{ "Black", Color::Black },
	};

	Color ConvertStringToColor(const std::string& color)
	{
		auto it = colorMap.find(color);
		if (it != colorMap.end())
		{
			return it->second;
		}
		throw UnknownStringColorException(color);
	}
};
