#pragma once

#include "./DocumentItem.h"
#include "./IDocument.h"
#include "./Item/Image.h"
#include "./Item/Paragraph.h"
#include <string>
#include <vector>

class Document : public IDocument
{
public:
	void SetTitle(const std::string& title) override
	{
		m_title = title;
	}

	const std::string GetTitle() const override
	{
		return m_title;
	}

	void InsertParagraph(size_t pos, const std::string& text) override
	{
		AssertInsertPositionCorrect(pos);
		auto paragraph = std::make_shared<Paragraph>(text);
		auto documentItem = DocumentItem(paragraph);

		InsertDocumentItem(documentItem, pos);
	}

	void InsertImage(size_t pos, const std::string& path, size_t width, size_t height) override
	{
		AssertInsertPositionCorrect(pos);
		auto image = std::make_shared<Image>(path, width, height);
		auto documentItem = DocumentItem(image);

		InsertDocumentItem(documentItem, pos);
	}

	std::string ReplaceText(size_t pos, const std::string& text) override
	{
		AssertPositionCorrect(pos);
		AssertItemIsParagraph(m_items[pos]);
		auto paragraph = m_items[pos].GetParagraph();
		std::string prevText = paragraph->GetText();

		paragraph->SetText(text);
		return prevText;
	}

	std::pair<size_t, size_t> ResizeImage(size_t pos, size_t width, size_t height) override
	{
		AssertPositionCorrect(pos);
		AssertItemIsImage(m_items[pos]);
		auto image = m_items[pos].GetImage();
		std::pair prevSize(image->GetWidth(), image->GetHeight());

		image->SetWidth(width);
		image->SetHeight(height);
		return prevSize;
	}

	void DeleteItem(size_t pos) override
	{
		if (pos < m_items.size())
		{
			m_items.erase(m_items.begin() + pos);
		}
	}

	size_t GetItemsCount() const override
	{
		return m_items.size();
	}

	DocumentItem GetItem(size_t pos) override
	{
		AssertPositionCorrect(pos);
		return m_items[pos];
	}

	std::vector<DocumentItem> ListItems() const override
	{
		return m_items;
	}

private:
	std::string m_title = "new document";
	std::vector<DocumentItem> m_items;

	void AssertItemIsParagraph(const DocumentItem& item)
	{
		if (item.GetParagraph() == nullptr)
		{
			throw std::runtime_error("Item dont paragraph");
		}
	}

	void AssertItemIsImage(const DocumentItem& item)
	{
		if (item.GetImage() == nullptr)
		{
			throw std::runtime_error("Item dont image");
		}
	}

	void AssertInsertPositionCorrect(size_t pos) const
	{
		if (pos > m_items.size())
		{
			throw std::runtime_error("Position is out of range. Document size: " + std::to_string(m_items.size()));
		}
	}

	void AssertPositionCorrect(size_t pos) const
	{
		if (pos >= m_items.size())
		{
			throw std::runtime_error("Position is out of range. Document size: " + std::to_string(m_items.size()));
		}
	}

	void InsertDocumentItem(DocumentItem& documentItem, size_t pos)
	{
		if (pos >= m_items.size())
		{
			m_items.emplace_back(documentItem);
		}
		else
		{
			m_items.insert(m_items.begin() + pos, documentItem);
		}
	}
};