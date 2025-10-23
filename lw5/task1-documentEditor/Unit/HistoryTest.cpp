#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/DocumentEditor/History/History.h"
#include "./Mock/MockCommand.h"

TEST_CASE("Test push history")
{
	History history;
	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	history.Push(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);
}

TEST_CASE("Test push history overflow count command")
{
	History history;
	std::unique_ptr<MockCommand> command;

	for (size_t i = 0; i < 10; ++i)
	{
		command = std::make_unique<MockCommand>("name");
		history.Push(std::move(command));

		REQUIRE(history.GetSize() == i + 1);
	}

	REQUIRE(history.GetSize() == 10);
	command = std::make_unique<MockCommand>("end");
	auto* commandPtr = command.get();
	history.Push(std::move(command));

	REQUIRE(history.GetSize() == 10);
	REQUIRE(commandPtr->GetName() == "end");
}

TEST_CASE("Test pop empty history")
{
	History history;

	REQUIRE(history.GetSize() == 0);
	REQUIRE_NOTHROW(history.Pop());
	REQUIRE(history.GetSize() == 0);
}

TEST_CASE("Test pop history")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	history.Push(std::move(command));

	REQUIRE(history.GetSize() == 1);
	REQUIRE_NOTHROW(history.Pop());
	REQUIRE(history.GetSize() == 0);
}

TEST_CASE("Test peak empty history")
{
	History history;

	auto command = history.Peek();

	REQUIRE(command == nullptr);
}

TEST_CASE("Test peak history")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	history.Push(std::move(command));

	REQUIRE(history.GetSize() == 1);

	auto hCommand = history.Peek();
	REQUIRE(hCommand != nullptr);
	REQUIRE(history.GetSize() == 1);
}

TEST_CASE("Test CanUndo empty history")
{
	History history;

	REQUIRE(history.CanUndo() == false);
}

TEST_CASE("Test CanUndo dont empty history")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	history.Push(std::move(command));

	REQUIRE(history.CanUndo() == true);
}

TEST_CASE("Test CanRedo empty history")
{
	History history;

	REQUIRE(history.CanRedo() == false);
}

TEST_CASE("Test CanRedo dont empty history")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	history.Push(std::move(command));

	REQUIRE(history.CanRedo() == false);
}

TEST_CASE("Test CanRedo dont empty history after Undo")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	history.Push(std::move(command));
	history.Undo();

	REQUIRE(history.CanRedo() == true);
}

TEST_CASE("Test Undo dont empty history")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	history.Push(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);

	history.Undo();
	REQUIRE(commandPtr->GetStatus() == false);
}

TEST_CASE("Test Undo empty history")
{
	History history;

	REQUIRE_NOTHROW(history.Undo());
}

TEST_CASE("Test Redo dont empty history after Undo")
{
	History history;

	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	history.Push(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);

	history.Undo();
	REQUIRE(commandPtr->GetStatus() == false);

	history.Redo();
	REQUIRE(commandPtr->GetStatus() == true);
}

TEST_CASE("Test Redo empty history")
{
	History history;

	REQUIRE_NOTHROW(history.Redo());
}