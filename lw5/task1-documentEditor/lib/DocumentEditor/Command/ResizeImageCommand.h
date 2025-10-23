#pragma once

#include "../../Document/IDocument.h"
#include "./ICommand.h"

class ResizeImageCommand : public ICommand
{
public:
	ResizeImageCommand(
		Document& document,
		size_t width,
		size_t height,
		size_t pos)
		: m_document(document)
		, m_pos(pos - 1)
		, m_width(width)
		, m_height(height)
	{
	}

	ResizeImageCommand(IDocument& document, size_t width, size_t height)
		: m_document(document)
		, m_width(width)
		, m_height(height)
	{
		m_pos = m_document.GetItemsCount() - 1;
	}

	void Execute() override
	{
		auto prevSize = m_document.ResizeImage(m_pos, m_width, m_height);
		m_prevWidth = prevSize.first;
		m_prevHeight = prevSize.second;
	}

	void UnExecute() override
	{
		m_document.ResizeImage(m_pos, m_prevWidth, m_prevHeight);
	}

	size_t GetPos()
	{
		return m_pos;
	}

private:
	IDocument& m_document;
	size_t m_pos;
	size_t m_prevWidth;
	size_t m_prevHeight;
	size_t m_width;
	size_t m_height;
};