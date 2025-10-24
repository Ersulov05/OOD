#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Document/Document.h"
#include "../lib/DocumentEditor/Command/ReplaceTextCommand.h"
#include "../lib/DocumentEditor/Command/ResizeImageCommand.h"
#include "../lib/DocumentEditor/Command/SetTitleCommand.h"
#include "./Mock/MockCommand.h"
#include "./Mock/MockDocumentEditor.h"

TEST_CASE("Test Execute DocumentEditor")
{
	MockDocumentEditor documentEditor;
	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	documentEditor.Execute(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);
}

TEST_CASE("Test multi Execute DocumentEditor")
{
	MockDocumentEditor documentEditor;
	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	documentEditor.Execute(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	auto command2 = std::make_unique<MockCommand>("name2");
	auto* command2Ptr = command2.get();
	REQUIRE(command2Ptr->GetStatus() == false);

	documentEditor.Execute(std::move(command2));
	REQUIRE(command2Ptr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 2);
}

TEST_CASE("Test Undo DocumentEditor")
{
	MockDocumentEditor documentEditor;
	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	documentEditor.Execute(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	documentEditor.Undo();
	REQUIRE(commandPtr->GetStatus() == false);
	REQUIRE(documentEditor.GetHistory().GetSize() == 0);
}

TEST_CASE("Test Undo DocumentEditor with empty history")
{
	MockDocumentEditor documentEditor;

	REQUIRE_THROWS(documentEditor.Undo());
}

TEST_CASE("Test Redo DocumentEditor with dont empty history after Undo")
{
	MockDocumentEditor documentEditor;
	auto command = std::make_unique<MockCommand>("name");
	auto* commandPtr = command.get();
	REQUIRE(commandPtr->GetStatus() == false);

	documentEditor.Execute(std::move(command));
	REQUIRE(commandPtr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	documentEditor.Undo();
	REQUIRE(commandPtr->GetStatus() == false);
	REQUIRE(documentEditor.GetHistory().GetSize() == 0);

	documentEditor.Redo();
	REQUIRE(commandPtr->GetStatus() == true);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);
}

TEST_CASE("Test Redo DocumentEditor with empty history")
{
	MockDocumentEditor documentEditor;

	REQUIRE_THROWS(documentEditor.Redo());
}

TEST_CASE("Test Execute DocumentEditor with Merge SetTitleCommand")
{
	Document document;
	MockDocumentEditor documentEditor;
	REQUIRE(document.GetTitle() == "new document");

	auto command = std::make_unique<SetTitleCommand>(document, "title");
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetTitle() == "title");
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	command = std::make_unique<SetTitleCommand>(document, "newTitle");
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetTitle() == "newTitle");
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	documentEditor.Undo();
	REQUIRE(document.GetTitle() == "new document");
	REQUIRE(documentEditor.GetHistory().GetSize() == 0);
}

TEST_CASE("Test Execute DocumentEditor with Merge ReplaceTextCommand")
{
	Document document;
	MockDocumentEditor documentEditor;
	document.InsertParagraph(0, "paragraph");
	REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "paragraph");

	auto command = std::make_unique<ReplaceTextCommand>(document, "text");
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "text");
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	command = std::make_unique<ReplaceTextCommand>(document, "newText");
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "newText");
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	documentEditor.Undo();
	REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "paragraph");
	REQUIRE(documentEditor.GetHistory().GetSize() == 0);
}

TEST_CASE("Test Execute DocumentEditor with Merge ResizeImageCommand")
{
	Document document;
	MockDocumentEditor documentEditor;
	document.InsertImage(0, "path", 100, 100);
	REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 100);
	REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 100);

	auto command = std::make_unique<ResizeImageCommand>(document, 200, 200);
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 200);
	REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	command = std::make_unique<ResizeImageCommand>(document, 300, 300);
	documentEditor.Execute(std::move(command));
	REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
	REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 300);
	REQUIRE(documentEditor.GetHistory().GetSize() == 1);

	documentEditor.Undo();
	REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 100);
	REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 100);
	REQUIRE(documentEditor.GetHistory().GetSize() == 0);
}