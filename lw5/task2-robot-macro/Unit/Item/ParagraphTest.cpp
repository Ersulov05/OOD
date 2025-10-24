#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../../lib/Document/Item/Paragraph.h"

TEST_CASE("Test Create Paragraph")
{
	auto paragraph = Paragraph("text");

	REQUIRE(paragraph.GetText() == "text");
}

TEST_CASE("Test Create Paragraph with empty text")
{
	auto paragraph = Paragraph("");

	REQUIRE(paragraph.GetText() == "");
}

TEST_CASE("Test SetText Success")
{
	auto paragraph = Paragraph("text");

	REQUIRE(paragraph.GetText() == "text");

	paragraph.SetText("xx xx");
	REQUIRE(paragraph.GetText() == "xx xx");
}

TEST_CASE("Test Set Empty Text Success")
{
	auto paragraph = Paragraph("text");

	REQUIRE(paragraph.GetText() == "text");

	paragraph.SetText("");
	REQUIRE(paragraph.GetText() == "");
}