#pragma once
#include "../../CriptUtils/CriptUtils.h"
#include "./CInputStreamDecorator.h"

class CDecryptInputStream : public CInputStreamDecorator
{
public:
	CDecryptInputStream(IInputStreamPtr&& inputStream, uint8_t key)
		: CInputStreamDecorator(std::move(inputStream))
		, m_key(key)
	{
	}

	uint8_t ReadByte() override
	{
		uint8_t byte = m_inputStream->ReadByte();

		return DecryptByte(byte, m_key);
	}

	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override
	{
		const std::streamsize bytesRead = m_inputStream->ReadBlock(dstBuffer, size);
		const auto data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < bytesRead; ++i)
		{
			data[i] = DecryptByte(data[i], m_key);
		}

		return bytesRead;
	}

private:
	uint8_t m_key;
};
