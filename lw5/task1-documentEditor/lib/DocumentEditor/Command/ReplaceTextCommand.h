#pragma once

#include "../../Document/IDocument.h"
#include "./ICommand.h"

class ReplaceTextCommand : public ICommand
{
public:
	ReplaceTextCommand(IDocument& document, const std::string& text)
		: m_document(document)
		, m_text(text)
	{
		m_pos = m_document.GetItemsCount() - 1;
	}

	ReplaceTextCommand(IDocument& document, const std::string& text, size_t pos)
		: m_document(document)
		, m_text(text)
		, m_pos(pos - 1)
	{
	}

	void Execute() override
	{
		m_prevText = m_document.ReplaceText(m_pos, m_text);
	}

	void UnExecute() override
	{
		m_document.ReplaceText(m_pos, m_prevText);
	}

	size_t GetPos()
	{
		return m_pos;
	}

private:
	IDocument& m_document;
	std::string m_text;
	std::string m_prevText;
	size_t m_pos;
};