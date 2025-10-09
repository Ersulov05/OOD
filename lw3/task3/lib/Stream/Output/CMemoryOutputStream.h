#pragma once

#include "./IOutputStream.h"
#include <fstream>
#include <vector>

class CMemoryOutputStream final : public IOutputStream
{
public:
	void WriteByte(const uint8_t data) override
	{
		AssertOpened();
		m_data.push_back(data);
	}

	void WriteBlock(const void* srcData, const std::streamsize size) override
	{
		AssertOpened();
		if (size == 0)
			return;

		const auto* bytes = static_cast<const uint8_t*>(srcData);
		m_data.insert(m_data.end(), bytes, bytes + size);
	}

	void Close() override
	{
		m_isOpen = false;
	}

private:
	bool m_isOpen = true;
	std::vector<uint8_t> m_data;

	void AssertOpened() const
	{
		if (!m_isOpen)
		{
			throw std::logic_error("File is closed");
		}
	}
};