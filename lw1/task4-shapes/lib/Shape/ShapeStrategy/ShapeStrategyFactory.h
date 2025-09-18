#pragma once

#include "./CircleStrategy.h"
#include "./LineStrategy.h"
#include "./RectStrategy.h"
#include "./TextStrategy.h"
#include "./TriangleStrategy.h"
#include "IShapeStrategy.h"
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

class ShapeStrategyFactory
{
public:
	using StrategyCreator = std::function<std::unique_ptr<IShapeStrategy>(const std::vector<std::string>&)>;

	std::unique_ptr<IShapeStrategy> CreateStrategy(const std::string& type, const std::vector<std::string>& params = {}) const
	{
		auto it = m_strategyCreators.find(type);
		if (it == m_strategyCreators.end())
		{
			throw std::invalid_argument("Unknown shape type: " + type);
		}
		return it->second(params);
	}

private:
	std::map<std::string, StrategyCreator> m_strategyCreators = {
		{ "circle", [](const std::vector<std::string>& params) { return std::make_unique<CircleStrategy>(params); } },
		{ "rectangle", [](const std::vector<std::string>& params) { return std::make_unique<RectStrategy>(params); } },
		{ "triangle", [](const std::vector<std::string>& params) { return std::make_unique<TriangleStrategy>(params); } },
		{ "line", [](const std::vector<std::string>& params) { return std::make_unique<LineStrategy>(params); } },
		{ "text", [](const std::vector<std::string>& params) { return std::make_unique<TextStrategy>(params); } },
	};
};