#pragma once
#include "../../CriptUtils/CriptUtils.h"
#include "./COutputStreamDecorator.h"
#include <vector>

class CEncryptOutputStream : public COutputStreamDecorator
{
public:
	CEncryptOutputStream(IOutputStreamPtr&& outputStream, uint8_t key)
		: COutputStreamDecorator(std::move(outputStream))
		, m_key(key)
	{
	}

	void WriteByte(const uint8_t data) override
	{
		const uint8_t encryptedByte = CryptByte(data, m_key);
		m_outputStream->WriteByte(encryptedByte);
	}

	void WriteBlock(const void* srcData, const std::streamsize size) override
	{
		const auto* data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}

private:
	uint8_t m_key;
};
