#pragma once
#include "../../CriptUtils/CriptUtils.h"
#include "./COutputStreamDecorator.h"
#include <vector>

class CCompressOutputStream : public COutputStreamDecorator
{
public:
	CCompressOutputStream(IOutputStreamPtr&& outputStream)
		: COutputStreamDecorator(std::move(outputStream))
	{
	}

	void WriteByte(const uint8_t data) override
	{
		if (m_currentCount == 0)
		{
			m_currentByte == data;
		}
		if (data == m_currentByte && m_currentCount != UINT8_MAX)
		{
			++m_currentCount;
		}
		else
		{
			SaveCompress();
			m_currentByte = data;
			m_currentCount = 1;
		}
	}

	void WriteBlock(const void* srcData, const std::streamsize size) override
	{
		const auto* data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}

	void Close() override
	{
		SaveCompress();
		m_outputStream->Close();
	}

private:
	uint8_t m_currentCount = 0;
	uint8_t m_currentByte = 0;

	void SaveCompress()
	{
		if (m_currentCount > 0)
		{
			m_outputStream->WriteByte(m_currentByte);
			m_outputStream->WriteByte(m_currentCount);
		}
		m_currentCount = 0;
	}
};
