#pragma once
#include "./IInputStream.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(const std::string& fileName)
		: m_file(fileName, std::ios::binary)
	{
		if (!m_file.is_open() || m_file.bad())
		{
			throw std::ios_base::failure("Failed to open file");
		}
	}

	bool IsEOF() const override
	{
		AssertFileOpened();

		return m_file.peek() == std::char_traits<char>::eof();
	}

	uint8_t ReadByte() override
	{
		AssertFileOpened();
		char byte; // проверить всё ли хорошо
		m_file.read(&byte, sizeof(byte));

		if (m_file.bad())
		{
			throw std::ios_base::failure("Failed to read byte");
		}

		if (m_file.eof() || m_file.fail())
		{
			throw std::ios_base::failure("End of file reached while reading byte");
		}

		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override
	{
		AssertFileOpened();
		m_file.read(static_cast<char*>(dstBuffer), size);
		if (m_file.bad())
		{
			throw std::ios_base::failure("Failed read block");
		}

		return m_file.gcount();
	}

	void Close() override
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

	~CFileInputStream() override
	{
		Close();
	}

private:
	mutable std::ifstream m_file;

	void AssertFileOpened() const
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File closed");
		}
	}
};