#pragma once

#include "../../Document/IDocument.h"
#include "./ICommand.h"

class SetTitleCommand : public ICommand
{
public:
	SetTitleCommand(IDocument& document, const std::string& title)
		: m_document(document)
		, m_title(title)
	{
	}

	void Execute() override
	{
		m_prevTitle = m_document.GetTitle();
		m_document.SetTitle(m_title);
	}

	void UnExecute() override
	{
		m_document.SetTitle(m_prevTitle);
	}

private:
	IDocument& m_document;
	std::string m_title;
	std::string m_prevTitle;
};