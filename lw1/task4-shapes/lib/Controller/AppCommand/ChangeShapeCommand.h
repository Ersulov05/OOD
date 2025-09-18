#pragma once

#include "../../Shape/ShapeStrategy/ShapeStrategyFactory.h"
#include "./AppCommand.h"

namespace app
{
class ChangeShapeCommand : public AppCommand
{
public:
	ChangeShapeCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, shapes::Picture& picture, gfx::CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 2);
		output << "Change shape" << std::endl;

		auto shapeId = m_parameters[0];
		auto type = m_parameters[1];

		auto params = std::vector<std::string>(m_parameters.begin() + 2, m_parameters.end());
		auto shapeStrategy = m_shapeStrategyFactory.CreateStrategy(type, params);

		picture.ChangeShapeStrategy(shapeId, std::move(shapeStrategy));
	}

private:
	ShapeStrategyFactory m_shapeStrategyFactory;
};
} // namespace app