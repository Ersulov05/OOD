#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Document/Document.h"

TEST_CASE("Test Set Title")
{
	Document doc;
	REQUIRE(doc.GetTitle() == "new document");

	doc.SetTitle("hello");
	REQUIRE(doc.GetTitle() == "hello");
}

TEST_CASE("Test insert paragraph")
{
	Document doc;

	doc.InsertParagraph(0, "hello");

	auto item = doc.GetItem(0);
	auto paragraph = item.GetParagraph();

	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "hello");
}

TEST_CASE("Test insert paragraph in Uncorrect position")
{
	Document doc;

	REQUIRE_THROWS(doc.InsertParagraph(1, "hello"));
}

TEST_CASE("Test multi insert paragraph")
{
	Document doc;

	doc.InsertParagraph(0, "hello");
	doc.InsertParagraph(0, "hello2");

	auto item = doc.GetItem(0);
	auto paragraph = item.GetParagraph();

	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "hello2");

	item = doc.GetItem(1);
	paragraph = item.GetParagraph();

	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "hello");
}

TEST_CASE("Test insert image")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);

	auto item = doc.GetItem(0);
	auto image = item.GetImage();

	REQUIRE(image != nullptr);
	REQUIRE(image->GetPath() == "path");
	REQUIRE(image->GetHeight() == 100);
	REQUIRE(image->GetWidth() == 200);
}

TEST_CASE("Test multi insert image")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);
	doc.InsertImage(0, "path2", 300, 200);

	auto item = doc.GetItem(0);
	auto image = item.GetImage();

	REQUIRE(image != nullptr);
	REQUIRE(image->GetPath() == "path2");
	REQUIRE(image->GetHeight() == 200);
	REQUIRE(image->GetWidth() == 300);

	item = doc.GetItem(1);
	image = item.GetImage();

	REQUIRE(image != nullptr);
	REQUIRE(image->GetPath() == "path");
	REQUIRE(image->GetHeight() == 100);
	REQUIRE(image->GetWidth() == 200);
}

TEST_CASE("Test insert image in Uncorrect position")
{
	Document doc;

	REQUIRE_THROWS(doc.InsertImage(1, "path", 200, 100));
}

TEST_CASE("Test resize image")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);
	auto image = doc.GetItem(0).GetImage();

	REQUIRE(image != nullptr);
	REQUIRE(image->GetHeight() == 100);
	REQUIRE(image->GetWidth() == 200);

	doc.ResizeImage(0, 300, 300);
	image = doc.GetItem(0).GetImage();
	REQUIRE(image != nullptr);
	REQUIRE(image->GetHeight() == 300);
	REQUIRE(image->GetWidth() == 300);
}

TEST_CASE("Test resize image with Uncorrect position")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);
	auto image = doc.GetItem(0).GetImage();

	REQUIRE(image != nullptr);
	REQUIRE(image->GetHeight() == 100);
	REQUIRE(image->GetWidth() == 200);

	REQUIRE_THROWS(doc.ResizeImage(1, 300, 300));
}

TEST_CASE("Test resize image with Dont ImageItem position")
{
	Document doc;

	doc.InsertParagraph(0, "text");
	auto image = doc.GetItem(0).GetImage();
	REQUIRE(image == nullptr);

	REQUIRE_THROWS(doc.ResizeImage(0, 300, 300));
}

TEST_CASE("Test replace text")
{
	Document doc;

	doc.InsertParagraph(0, "text");
	auto paragraph = doc.GetItem(0).GetParagraph();

	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "text");

	doc.ReplaceText(0, "newtext");
	paragraph = doc.GetItem(0).GetParagraph();
	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "newtext");
}

TEST_CASE("Test replace text with Uncorrect position")
{
	Document doc;

	doc.InsertParagraph(0, "text");
	auto paragraph = doc.GetItem(0).GetParagraph();

	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == "text");

	REQUIRE_THROWS(doc.ReplaceText(1, "newtext"));
}

TEST_CASE("Test resize image with Dont ParagraphItem position")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);
	auto paragraph = doc.GetItem(0).GetParagraph();
	REQUIRE(paragraph == nullptr);

	REQUIRE_THROWS(doc.ReplaceText(0, "newtext"));
}

TEST_CASE("Test delete item")
{
	Document doc;

	doc.InsertImage(0, "path", 200, 100);
	doc.InsertImage(0, "path2", 300, 400);

	REQUIRE(doc.GetItemsCount() == 2);

	doc.DeleteItem(0);
	REQUIRE(doc.GetItemsCount() == 1);
}

TEST_CASE("Test delete empty items")
{
	Document doc;

	REQUIRE_NOTHROW(doc.DeleteItem(0));
}
