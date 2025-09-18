#pragma once

#include "../../Color/Color.h"
#include "../../Shape/Shape.h"
#include "../../Shape/ShapeStrategy/ShapeStrategyFactory.h"
#include "./AppCommand.h"

class MoveShapeCommand : public AppCommand
{
public:
	MoveShapeCommand(const std::vector<std::string>& parameters)
		: AppCommand(parameters)
	{
	}

	void Execute(std::ostream& output, Picture& picture, CCanvas& canvas) override
	{
		AssertCorrectCountArguments(m_parameters.size(), 3);

		auto shapeId = m_parameters[0];
		auto dx = std::stod(m_parameters[1]);
		auto dy = std::stod(m_parameters[2]);

		picture.MoveShape(shapeId, dx, dy);
		output << "Move shape" << std::endl;
	}

private:
	ShapeStrategyFactory m_shapeStrategyFactory;
};
