#pragma once

#include "../Document/IDocument.h"
#include "../ImageService/ImageService.h"
#include <fstream>
#include <iomanip>
#include <sstream>

class HTMLSaver
{
public:
	static void Save(const IDocument& document, const std::string& fileName)
	{
		std::string imageDir = GetFileNameWithoutExtension(fileName) + "dir";
		auto imageService = ImageService(imageDir);

		std::ofstream file(fileName);
		if (!file.is_open())
		{
			throw std::runtime_error("Cannot open file for writing: " + fileName);
		}

		file << GenerateHTML(document, imageService);
	}

private:
	static std::string GetFileNameWithoutExtension(const std::string& fileName)
	{
		size_t pos = fileName.find_last_of('.');

		if (pos == std::string::npos || pos == 0)
		{
			return fileName;
		}

		return fileName.substr(0, pos);
	}

	static std::string GenerateHTML(const IDocument& document, ImageService& imageService)
	{
		std::ostringstream html;

		html << "<!DOCTYPE html>\n";
		html << "<html>\n";
		html << "<head>\n";
		html << "    <meta charset=\"utf-8\">\n";
		html << "    <title>" << document.GetTitle() << "</title>\n";
		html << "</head>\n";
		html << "<body>\n";
		html << "    <h1>" << document.GetTitle() << "</h1>\n";

		auto items = document.ListItems();
		for (const auto& item : items)
		{
			html << "    " << GenerateItemHTML(item, imageService);
		}

		html << "</body>\n";
		html << "</html>";

		return html.str();
	}

	static std::string GenerateItemHTML(const DocumentItem& item, ImageService& imageService)
	{

		std::ostringstream html;

		if (auto paragraph = item.GetParagraph())
		{
			html << "<p>" << paragraph->GetText() << "</p>\n";
		}
		else if (auto image = item.GetImage())
		{
			auto imagePath = imageService.SaveImage(image->GetPath());
			html << "<img src=\"" << imagePath << "\" "
				 << "width=\"" << image->GetWidth() << "\" "
				 << "height=\"" << image->GetHeight() << "\">\n";
		}

		return html.str();
	}
};