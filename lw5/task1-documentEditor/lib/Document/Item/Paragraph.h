#pragma once

#include "./IParagraph.h"
#include <string>

class Paragraph : public IParagraph
{
public:
	Paragraph(const std::string& text)
		: m_text(text)
	{
	}

	void SetText(const std::string& text) override
	{
		m_text = text;
	}

	const std::string GetText() const override
	{
		return m_text;
	}

private:
	std::string m_text;
};