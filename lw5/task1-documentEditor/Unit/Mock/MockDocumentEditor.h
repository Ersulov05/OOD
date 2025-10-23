#pragma once

#include "../../lib/DocumentEditor/DocumentEditor.h"

class MockDocumentEditor : public DocumentEditor
{
public:
	History& GetHistory()
	{
		return m_history;
	}
};