#pragma once
#include "./Document/Document.h"
#include "./Document/IDocument.h"
#include "./DocumentEditor/Command/InsertImageCommand.h"
#include "./DocumentEditor/Command/InsertParagraphCommand.h"
#include "./DocumentEditor/Command/ListItemsCommand.h"
#include "./DocumentEditor/Command/ReplaceTextCommand.h"
#include "./DocumentEditor/Command/ResizeImageCommand.h"
#include "./DocumentEditor/Command/SetTitleCommand.h"
#include "./DocumentEditor/DocumentEditor.h"
#include "./HTMLSaver/HTMLSaver.h"
#include "./ImageService/ImageService.h"
#include "./Menu/Menu.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class App
{
public:
	App()
	{
		SetupMenu();
	}

	void Run()
	{
		std::cout << "=== Система управления документом ===\n";
		std::cout << "Для просмотра команд введите 'help' или '?'\n\n";

		m_menu.Run();
	}

	~App()
	{
		m_imageService.DeleteDirImages();
	}

private:
	Menu m_menu = Menu(std::cin, std::cout);
	DocumentEditor m_documentEditor;
	Document m_document;
	ImageService m_imageService = ImageService("temp_images");

	void SetupMenu()
	{
		m_menu.AddItem(
			"InsertParagraph",
			"Usage: InsertParagraph <position>|end <text>. Inserts a paragraph into the specified position.",
			[&](std::istringstream& params) { HandleInsertParagraph(params); });

		m_menu.AddItem(
			"ResizeImage",
			"Usage: ResizeImage <position>|end <text>. Inserts a paragraph into the specified position.",
			[&](std::istringstream& params) { HandleResizeImage(params); });

		m_menu.AddItem(
			"InsertImage",
			"Usage: InsertImage <position>|end <text>. Inserts a paragraph into the specified position.",
			[&](std::istringstream& params) { HandleInsertImage(params); });

		m_menu.AddItem(
			"SetTitle",
			"Usage: SetTitle <text>.",
			[&](std::istringstream& params) { HandleSetTitle(params); });

		m_menu.AddItem(
			"ReplaceText",
			"Usage: SetTitle <text>.",
			[&](std::istringstream& params) { HandleReplaceText(params); });

		m_menu.AddItem(
			"Exit",
			"Usage: Exit.",
			[&](std::istringstream& params) { m_menu.Exit(); });

		m_menu.AddItem(
			"Save",
			"Usage: Save.",
			[&](std::istringstream& params) { HandleSave(params); });

		m_menu.AddItem(
			"Undo",
			"Usage: Undo.",
			[&](std::istringstream& params) { m_documentEditor.Undo(); });

		m_menu.AddItem(
			"Redo",
			"Usage: Redo.",
			[&](std::istringstream& params) { m_documentEditor.Redo(); });

		m_menu.AddItem(
			"List",
			"Usage: List.",
			[&](std::istringstream& params) { HandleListElements(); });
	}

	void HandleSave(std::istringstream& params)
	{
		std::string fileName;

		if (!(params >> fileName))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		HTMLSaver::Save(m_document, fileName);
	}

	void HandleInsertParagraph(std::istringstream& params)
	{
		std::string stringPosition;

		if (!(params >> stringPosition))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}
		std::string text = GetText(params);

		std::unique_ptr<InsertParagraphCommand> command;

		if (stringPosition == "end")
		{
			command = std::make_unique<InsertParagraphCommand>(m_document, text);
		}
		else
		{
			size_t position = GetPosition(stringPosition);
			command = std::make_unique<InsertParagraphCommand>(m_document, text, position);
		}

		m_documentEditor.Execute(std::move(command));
	}

	void HandleInsertImage(std::istringstream& params)
	{
		std::string stringPosition;
		std::string path;
		size_t width;
		size_t height;

		if (!(params >> stringPosition >> path >> width >> height))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		std::unique_ptr<InsertImageCommand> command;

		if (stringPosition == "end")
		{
			command = std::make_unique<InsertImageCommand>(m_document, m_imageService, path, width, height);
		}
		else
		{
			size_t position = GetPosition(stringPosition);
			command = std::make_unique<InsertImageCommand>(m_document, m_imageService, path, width, height, position);
		}

		m_documentEditor.Execute(std::move(command));
	}

	void HandleResizeImage(std::istringstream& params)
	{
		std::string stringPosition;
		size_t width;
		size_t height;

		if (!(params >> stringPosition >> width >> height))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		std::unique_ptr<ResizeImageCommand> command;

		if (stringPosition == "end")
		{
			command = std::make_unique<ResizeImageCommand>(m_document, width, height);
		}
		else
		{
			size_t position = GetPosition(stringPosition);
			command = std::make_unique<ResizeImageCommand>(m_document, width, height, position);
		}

		m_documentEditor.Execute(std::move(command));
	}

	void HandleReplaceText(std::istringstream& params)
	{
		std::string stringPosition;

		if (!(params >> stringPosition))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}
		std::string text = GetText(params);

		std::unique_ptr<ReplaceTextCommand> command;

		if (stringPosition == "end")
		{
			command = std::make_unique<ReplaceTextCommand>(m_document, text);
		}
		else
		{
			size_t position = GetPosition(stringPosition);
			command = std::make_unique<ReplaceTextCommand>(m_document, text, position);
		}

		m_documentEditor.Execute(std::move(command));
	}

	void HandleSetTitle(std::istringstream& params)
	{
		std::string title;

		if (!(params >> title))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		auto command = std::make_unique<SetTitleCommand>(m_document, title);

		m_documentEditor.Execute(std::move(command));
	}

	void HandleListElements()
	{
		auto command = std::make_unique<ListItemsCommand>(m_document, std::cout);
		command->Execute();
	}

	size_t GetPosition(const std::string& stringPosition)
	{
		try
		{
			return std::stoi(stringPosition);
		}
		catch (std::invalid_argument&)
		{
			throw std::runtime_error("Error: The position must be an uint or 'end'.");
		}
	}

	std::string GetText(std::istringstream& params)
	{
		std::string text;
		getline(params, text);

		return Trim(text);
	}

	std::string Trim(std::string& str)
	{
		auto start = str.find_first_not_of(" \t\n\r");
		if (start == std::string::npos)
		{
			return str;
		}

		auto end = str.find_last_not_of(" \t\n\r");
		return str.substr(start, end - start + 1);
	}
};
