#pragma once

#include "./Command/ICommand.h"
#include "./Command/ReplaceTextCommand.h"
#include "./Command/ResizeImageCommand.h"
#include "./Command/SetTitleCommand.h"
#include "./History/History.h"

class DocumentEditor
{
public:
	void Execute(std::unique_ptr<ICommand> command)
	{
		TryMergeReplaceTextCommand(command);
		TryMergeResizeImageCommand(command);
		TryMergeSetTitleCommand(command);

		m_history.Push(std::move(command));
	}

	void Undo()
	{
		AssertCanUndo();
		m_history.Undo();
	}

	void Redo()
	{
		AssertCanRedo();
		m_history.Redo();
	}

protected:
	History m_history;

private:
	void AssertCanUndo()
	{
		if (!m_history.CanUndo())
		{
			throw std::runtime_error("Dont can Undo");
		}
	}

	void AssertCanRedo()
	{
		if (!m_history.CanRedo())
		{
			throw std::runtime_error("Dont can Redo");
		}
	}

	void TryMergeReplaceTextCommand(std::unique_ptr<ICommand>& command)
	{
		auto newCmd = dynamic_cast<ReplaceTextCommand*>(command.get());
		if (!newCmd)
			return;

		auto lastCmd = dynamic_cast<ReplaceTextCommand*>(m_history.Peek());
		if (!lastCmd)
			return;

		if (lastCmd->GetPos() == newCmd->GetPos())
		{
			m_history.Undo();
		}
	}

	void TryMergeResizeImageCommand(std::unique_ptr<ICommand>& command)
	{
		auto newCmd = dynamic_cast<ResizeImageCommand*>(command.get());
		if (!newCmd)
			return;

		auto lastCmd = dynamic_cast<ResizeImageCommand*>(m_history.Peek());
		if (!lastCmd)
			return;

		if (lastCmd->GetPos() == newCmd->GetPos())
		{
			m_history.Undo();
		}
	}

	void TryMergeSetTitleCommand(std::unique_ptr<ICommand>& command)
	{
		if (
			dynamic_cast<SetTitleCommand*>(command.get())
			&& dynamic_cast<SetTitleCommand*>(m_history.Peek()))
		{
			m_history.Undo();
		}
	}
};