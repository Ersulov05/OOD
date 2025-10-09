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
		std::vector<uint8_t> encryptedData(size);
		for (std::streamsize i = 0; i < size; ++i)
		{
			encryptedData[i] = CryptByte(data[i], m_key);
		}
		m_outputStream->WriteBlock(encryptedData.data(), size);
	}

private:
	uint32_t m_key;
};
