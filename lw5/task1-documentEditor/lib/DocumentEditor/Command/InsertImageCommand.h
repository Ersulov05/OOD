#pragma once

#include "../../Document/IDocument.h"
#include "../../ImageService/ImageService.h"
#include "./ICommand.h"

class InsertImageCommand : public ICommand
{
public:
	InsertImageCommand(
		IDocument& document,
		ImageService& imageService,
		const std::string& path,
		size_t width,
		size_t height,
		size_t pos)
		: m_document(document)
		, m_imageService(imageService)
		, m_path(imageService.SaveImage(path))
		, m_pos(pos)
		, m_width(width)
		, m_height(height)
	{
	}

	InsertImageCommand(IDocument& document, ImageService& imageService, const std::string& path, size_t width, size_t height)
		: m_document(document)
		, m_imageService(imageService)
		, m_path(imageService.SaveImage(path))
		, m_width(width)
		, m_height(height)
	{
		m_pos = m_document.GetItemsCount();
	}

	void Execute() override
	{
		m_document.InsertImage(m_pos, m_path, m_width, m_height);
		m_shouldDelete = false;
	}

	void UnExecute() override
	{
		m_document.DeleteItem(m_pos);
		m_shouldDelete = true;
	}

	~InsertImageCommand()
	{
		if (m_shouldDelete)
		{
			m_imageService.DeleteImage(m_path);
		}
	}

private:
	IDocument& m_document;
	ImageService& m_imageService;
	std::string m_path;
	size_t m_pos;
	size_t m_width;
	size_t m_height;
	bool m_shouldDelete = false;
};