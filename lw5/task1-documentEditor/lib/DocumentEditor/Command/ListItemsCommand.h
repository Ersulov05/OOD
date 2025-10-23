#pragma once

#include "../../Document/IDocument.h"
#include "../../ImageService/ImageService.h"
#include "./ICommand.h"
#include <string>

class ListItemsCommand : public ICommand
{
public:
	ListItemsCommand(IDocument& document, std::ostream& output)
		: m_document(document)
		, m_output(output)
	{
	}

	void Execute() override
	{
		auto items = m_document.ListItems();

		m_output << "Title: " << m_document.GetTitle() << std::endl;
		size_t i = 1;
		for (auto& item : items)
		{
			m_output << i << ". " << GenerateItemString(item) << std::endl;
			++i;
		}
	}

	void UnExecute() override
	{
	}

private:
	IDocument& m_document;
	std::ostream& m_output;

	static std::string GenerateItemString(const DocumentItem& item)
	{
		if (auto paragraph = item.GetParagraph())
		{
			return "Paragraph: " + paragraph->GetText();
		}
		else if (auto image = item.GetImage())
		{
			return "Image: " + std::to_string(image->GetWidth()) + " " + std::to_string(image->GetHeight()) + " " + image->GetPath();
		}

		return "";
	}
};