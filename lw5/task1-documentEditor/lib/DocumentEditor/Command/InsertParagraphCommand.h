#pragma once

#include "../../Document/IDocument.h"
#include "./ICommand.h"

class InsertParagraphCommand : public ICommand
{
public:
	InsertParagraphCommand(IDocument& document, const std::string& text, size_t pos)
		: m_document(document)
		, m_text(text)
		, m_pos(pos)
	{
	}

	InsertParagraphCommand(IDocument& document, const std::string& text)
		: m_document(document)
		, m_text(text)
	{
		m_pos = m_document.GetItemsCount();
	}

	void Execute() override
	{
		m_document.InsertParagraph(m_pos, m_text);
	}

	void UnExecute() override
	{
		m_document.DeleteItem(m_pos);
	}

private:
	IDocument& m_document;
	std::string m_text;
	size_t m_pos;
};