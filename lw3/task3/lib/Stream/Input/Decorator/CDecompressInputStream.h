#pragma once
#include "../../CriptUtils/CriptUtils.h"
#include "./CInputStreamDecorator.h"

class CDecompressInputStream : public CInputStreamDecorator
{
public:
	CDecompressInputStream(IInputStreamPtr&& inputStream)
		: CInputStreamDecorator(std::move(inputStream))
	{
	}

	uint8_t ReadByte() override
	{
		uint8_t byte = 0;
		ReadDecompressByte(byte);

		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override
	{
		uint8_t byte = 0;
		std::streamsize bytesRead = 0;
		auto* buffer = static_cast<uint8_t*>(dstBuffer);

		for (bytesRead; bytesRead < size; ++bytesRead)
		{
			if (IsEOF() || !ReadDecompressByte(byte))
			{
				break;
			}
			buffer[bytesRead] = byte;
		}

		return bytesRead;
	}

	bool IsEOF() const override
	{
		return m_currentCount == 0 && m_inputStream->IsEOF();
	}

private:
	uint8_t m_currentCount = 0;
	uint8_t m_currentByte = 0;

	bool ReadDecompressByte(uint8_t& byte)
	{
		if (m_currentCount == 0)
		{
			if (m_inputStream->IsEOF())
			{
				return false;
			}
			m_currentByte = m_inputStream->ReadByte();
			m_currentCount = !m_inputStream->IsEOF()
				? m_inputStream->ReadByte()
				: 1;
		}
		byte = m_currentByte;
		--m_currentCount;

		return true;
	}
};
