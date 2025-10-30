#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Document/DocumentItem.h"
#include "../lib/Document/Item/Image.h"
#include "../lib/Document/Item/Paragraph.h"

TEST_CASE("Test create DocumentItem with Paragraph")
{
	auto paragraph = std::make_shared<Paragraph>("text");
	DocumentItem item(paragraph);

	REQUIRE(item.GetParagraph() != nullptr);
	REQUIRE(item.GetImage() == nullptr);
}

TEST_CASE("Test create DocumentItem with Image")
{
	auto image = std::make_shared<Image>("path", 100, 200);
	DocumentItem item(image);

	REQUIRE(item.GetParagraph() == nullptr);
	REQUIRE(item.GetImage() != nullptr);
}