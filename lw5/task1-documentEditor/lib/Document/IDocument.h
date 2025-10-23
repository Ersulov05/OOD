#pragma once

#include "./DocumentItem.h"
#include <string>
#include <vector>

class IDocument
{
public:
	virtual void SetTitle(const std::string& title) = 0;
	virtual const std::string GetTitle() const = 0;
	virtual void InsertParagraph(size_t pos, const std::string& text) = 0;
	virtual void InsertImage(size_t pos, const std::string& path, size_t width, size_t height) = 0;
	virtual std::string ReplaceText(size_t pos, const std::string& text) = 0;
	virtual std::pair<size_t, size_t> ResizeImage(size_t pos, size_t width, size_t height) = 0;
	virtual void DeleteItem(size_t pos) = 0;
	virtual size_t GetItemsCount() const = 0;
	virtual DocumentItem GetItem(size_t pos) = 0;
	virtual std::vector<DocumentItem> ListItems() const = 0;
	virtual ~IDocument() = default;
};