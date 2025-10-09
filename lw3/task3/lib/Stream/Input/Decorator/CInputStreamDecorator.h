#pragma once
#include "../IInputStream.h"

class CInputStreamDecorator : public IInputStream
{
public:
	bool IsEOF() const override
	{
		return m_inputStream->IsEOF();
	}

	void Close() override
	{
		m_inputStream->Close();
	}

protected:
	CInputStreamDecorator(IInputStreamPtr&& inputStream)
		: m_inputStream(std::move(inputStream))
	{
	}

	IInputStreamPtr m_inputStream;
};