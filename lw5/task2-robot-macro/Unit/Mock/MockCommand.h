#pragma once

#include "../../lib/DocumentEditor/Command/ICommand.h"
#include <string>

class MockCommand : public ICommand
{
public:
	MockCommand(const std::string& name)
		: m_name(name)
	{
	}

	void Execute() override
	{
		m_status = true;
	}

	void UnExecute() override
	{
		m_status = false;
	}

	bool GetStatus() const
	{
		return m_status;
	}

	std::string GetName() const
	{
		return m_name;
	}

private:
	std::string m_name;
	bool m_status = false;
};