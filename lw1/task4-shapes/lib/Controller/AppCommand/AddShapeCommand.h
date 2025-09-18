#pragma once

#include "../../Color/Color.h"
#include "../../Shape/Shape.h"
#include "../../Shape/ShapeStrategy/ShapeStrategyFactory.h"
#include "./AppCommand.h"

class AddShapeCommand : public AppCommand
{
public:
	AddShapeCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 3);
		output << "Add shape" << std::endl;

		auto shapeId = m_parameters[0];
		auto color = StringToColor(m_parameters[1]);
		auto type = m_parameters[2];
		auto params = std::vector<std::string>(m_parameters.begin() + 3, m_parameters.end());
		auto shapeStrategy = m_shapeStrategyFactory.CreateStrategy(type, params);
		auto shape = std::make_unique<Shape>(shapeId, color, std::move(shapeStrategy));

		picture.AddShape(std::move(shape));
	}

private:
	ShapeStrategyFactory m_shapeStrategyFactory;
};
