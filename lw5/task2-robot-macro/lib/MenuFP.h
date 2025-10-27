#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class CMenuFP
{
public:
	typedef std::function<void()> Command;

	template <typename Commands>
	static Command CreateMacroCommand(Commands&& commands)
	{
		return [=] {
			for (auto& command : commands)
			{
				command();
			}
		};
	}

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while ((std::cout << ">")
			&& getline(std::cin, command)
			&& ExecuteCommand(command))
		{
		}
	}

	void ShowInstructions() const
	{
		std::cout << "Commands list:\n";
		for (auto& item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

	void AddMacroCommand(
		const std::string& shortcut,
		const std::string& description,
		const std::vector<std::string>& commandNames)
	{
		std::vector<Command> commands;
		for (const auto& command : commandNames)
		{
			const auto it = std::ranges::find_if(m_items, [&](const Item& item) {
				return item.shortcut == command;
			});
			if (it != m_items.end())
			{
				commands.push_back(it->command);
			}
		}

		m_items.emplace_back(shortcut, description, CreateMacroCommand(commands));
	}

	bool AreCommandExists(const std::string& shortcut)
	{
		const auto it = std::ranges::find_if(m_items, [&](const Item& item) {
			return item.shortcut == shortcut;
		});
		return it != m_items.end();
	}

private:
	bool ExecuteCommand(const std::string& command)
	{
		m_exit = false;
		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == command;
		});
		if (it != m_items.end())
		{
			it->command();
		}
		else
		{
			std::cout << "Unknown command\n";
		}
		return !m_exit;
	}

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
};