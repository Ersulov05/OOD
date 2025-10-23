#pragma once

#include "./IImage.h"
#include <string>

class Image : public IImage
{
public:
	Image(const std::string& path, size_t width, size_t height)
		: m_path(path)
		, m_width(width)
		, m_height(height)
	{
		AssertCorrectSize(width);
		AssertCorrectSize(height);
	}

	void SetWidth(size_t width) override
	{
		AssertCorrectSize(width);
		m_width = width;
	}

	void SetHeight(size_t height) override
	{
		AssertCorrectSize(height);
		m_height = height;
	}

	size_t GetWidth() const override
	{
		return m_width;
	}

	size_t GetHeight() const override
	{
		return m_height;
	}

	std::string GetPath() const override
	{
		return m_path;
	}

private:
	std::string m_path;
	size_t m_width;
	size_t m_height;
	const size_t MAX_SIZE = 10000;

	void AssertCorrectSize(size_t size)
	{
		if (size == 0 || size > MAX_SIZE)
		{
			throw std::runtime_error("Uncorrect image size");
		}
	}
};