#pragma once
#include <string>

class IImage
{
public:
	virtual void SetWidth(size_t width) = 0;
	virtual void SetHeight(size_t height) = 0;
	virtual size_t GetWidth() const = 0;
	virtual size_t GetHeight() const = 0;
	virtual std::string GetPath() const = 0;
	virtual ~IImage() = default;
};