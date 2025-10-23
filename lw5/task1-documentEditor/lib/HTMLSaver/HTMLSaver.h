#pragma once

#include "../Document/IDocument.h"
#include <fstream>
#include <iomanip>
#include <sstream>

class HTMLSaver
{
public:
	static void Save(const IDocument& document, const std::string& filePath)
	{
		std::ofstream file(filePath);
		if (!file.is_open())
		{
			throw std::runtime_error("Cannot open file for writing: " + filePath);
		}

		file << GenerateHTML(document);
	}

	static std::string GenerateHTML(const IDocument& document)
	{
		std::ostringstream html;

		html << "<!DOCTYPE html>\n";
		html << "<html>\n";
		html << "<head>\n";
		html << "    <meta charset=\"utf-8\">\n";
		html << "    <title>" << EscapeHTML(document.GetTitle()) << "</title>\n";
		html << "</head>\n";
		html << "<body>\n";
		html << "    <h1>" << EscapeHTML(document.GetTitle()) << "</h1>\n";

		auto items = document.ListItems();
		for (const auto& item : items)
		{
			html << "    " << GenerateItemHTML(item);
		}

		html << "</body>\n";
		html << "</html>";

		return html.str();
	}

private:
	static std::string GenerateItemHTML(const DocumentItem& item)
	{
		std::ostringstream html;

		if (auto paragraph = item.GetParagraph())
		{
			html << "<p>" << paragraph->GetText() << "</p>\n";
		}
		else if (auto image = item.GetImage())
		{
			html << "<img src=\"" << image->GetPath() << "\" "
				 << "width=\"" << image->GetWidth() << "\" "
				 << "height=\"" << image->GetHeight() << "\">\n";
		}

		return html.str();
	}
};