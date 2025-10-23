#pragma once

#include "../DocumentEditor/Command/ICommand.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Menu
{
public:
	Menu(std::istream& input, std::ostream& output)
		: m_input(input)
		, m_output(output)
	{
	}
	using Command = std::function<void(std::istringstream&)>;

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		const Command& command)
	{
		AssertShotcutUnique(shortcut);
		m_items.emplace_back(shortcut, description, std::move(command));
	}

	void Run()
	{
		m_exit = false;
		ShowInstructions();

		std::string command;
		while ((m_output << ">")
			&& getline(m_input, command))
		{
			try
			{
				if (!ExecuteCommand(command))
				{
					break;
				}
			}
			catch (std::exception& e)
			{
				m_output << e.what() << std::endl;
			}
		}
	}

	void ShowInstructions() const
	{
		m_output << "Commands list:\n";
		for (auto& item : m_items)
		{
			m_output << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

	bool ExecuteCommand(const std::string& command)
	{
		m_exit = false;
		std::istringstream iss(command);
		std::string name;
		iss >> name;

		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == name;
		});
		if (it != m_items.end())
		{
			it->command(iss);
		}
		else
		{
			throw std::runtime_error("Unknown command");
		}

		return !m_exit;
	}

private:
	void AssertShotcutUnique(const std::string& name)
	{
		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == name;
		});
		if (it != m_items.end())
		{
			throw std::runtime_error("Shortcut dont unique");
		}
	}

	struct Item
	{
		Item(std::string shortcut, std::string description, Command command)
			: shortcut(std::move(shortcut))
			, description(std::move(description))
			, command(std::move(command))
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
	std::istream& m_input;
	std::ostream& m_output;
};