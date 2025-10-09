#pragma once
#include "./IInputStream.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <vector>

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(const std::vector<uint8_t>& data)
		: m_data(data)
	{
	}

	bool IsEOF() const override
	{
		AssertOpened();
		return m_position >= m_data.size();
	}

	uint8_t ReadByte() override
	{
		AssertOpened();
		if (IsEOF())
		{
			throw std::ios_base::failure("Failed to read byte");
		}

		return m_data[m_position++];
	}

	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override
	{
		AssertOpened();
		auto* buffer = static_cast<uint8_t*>(dstBuffer);
		std::streamsize bytesRead = 0;

		while (bytesRead < size && !IsEOF())
		{
			buffer[bytesRead++] = m_data[m_position++];
		}

		return bytesRead;
	}

	void Close() override
	{
		m_isOpen = false;
	}

private:
	bool m_isOpen = true;
	std::vector<uint8_t> m_data;
	std::size_t m_position = 0;

	void AssertOpened() const
	{
		if (!m_isOpen)
		{
			throw std::logic_error("File closed");
		}
	}
};