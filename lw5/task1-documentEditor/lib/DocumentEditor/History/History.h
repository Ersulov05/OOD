#pragma once

#include "../Command/ICommand.h"
#include <deque>
#include <memory>
#include <stack>
#include <vector>

class History
{
public:
	void Push(std::unique_ptr<ICommand> command)
	{
		if (m_undoStack.size() >= m_maxSize)
		{
			m_undoStack.pop_front();
		}

		command->Execute();
		m_undoStack.push_back(std::move(command));
		m_redoStack.clear();
	}

	ICommand* Peek() const
	{
		return CanUndo()
			? m_undoStack.back().get()
			: nullptr;
	}

	void Pop()
	{
		if (CanUndo())
		{
			m_undoStack.pop_back();
		}
	}

	bool CanUndo() const
	{
		return !m_undoStack.empty();
	}

	bool CanRedo() const
	{
		return !m_redoStack.empty();
	}

	void Undo()
	{
		if (CanUndo())
		{
			auto command = std::move(m_undoStack.back());
			m_undoStack.pop_back();

			command->UnExecute();
			m_redoStack.push_back(std::move(command));
		}
	}

	void Redo()
	{
		if (CanRedo())
		{
			auto command = std::move(m_redoStack.back());
			m_redoStack.pop_back();

			command->Execute();
			m_undoStack.push_back(std::move(command));
		}
	}

	size_t GetSize()
	{
		return m_undoStack.size();
	}

private:
	size_t m_maxSize = 10;
	std::deque<std::unique_ptr<ICommand>> m_undoStack;
	std::deque<std::unique_ptr<ICommand>> m_redoStack;
};