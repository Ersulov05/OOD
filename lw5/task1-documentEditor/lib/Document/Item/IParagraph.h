#pragma once
#include <string>

class IParagraph
{
public:
	virtual void SetText(const std::string& text) = 0;
	virtual const std::string GetText() const = 0;
	virtual ~IParagraph() = default;
};