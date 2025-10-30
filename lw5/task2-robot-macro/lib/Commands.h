#pragma once
#include "ICommand.h"
#include "Robot.h"
#include <memory>
#include <vector>

class CTurnOnCommand : public ICommand
{
public:
	CTurnOnCommand(Robot& robot)
		: m_robot(robot)
	{
	}

	void Execute() override
	{
		m_robot.TurnOn();
	}

private:
	Robot& m_robot;
};

class CTurnOffCommand : public ICommand
{
public:
	CTurnOffCommand(Robot& robot)
		: m_robot(robot)
	{
	}
	void Execute() override
	{
		m_robot.TurnOff();
	}

private:
	Robot& m_robot;
};

class CWalkCommand : public ICommand
{
public:
	CWalkCommand(Robot& robot, WalkDirection direction)
		: m_robot(robot)
		, m_direction(direction)
	{
	}
	void Execute() override
	{
		m_robot.Walk(m_direction);
	}

private:
	Robot& m_robot;
	WalkDirection m_direction;
};

class CStopCommand : public ICommand
{
public:
	CStopCommand(Robot& robot)
		: m_robot(robot)
	{
	}
	void Execute() override
	{
		m_robot.Stop();
	}

private:
	Robot& m_robot;
};