#pragma once
#include "../IOutputStream.h"

class COutputStreamDecorator : public IOutputStream
{
public:
	void Close() override
	{
		m_outputStream->Close();
	}

protected:
	COutputStreamDecorator(IOutputStreamPtr&& outputStream)
		: m_outputStream(std::move(outputStream))
	{
	}

	IOutputStreamPtr m_outputStream;
};