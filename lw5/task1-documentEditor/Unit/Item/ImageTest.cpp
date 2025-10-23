#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../../lib/Document/Item/Image.h"

TEST_CASE("Test Create Image")
{
	auto image = Image("path", 300, 400);

	REQUIRE(image.GetPath() == "path");
	REQUIRE(image.GetWidth() == 300);
	REQUIRE(image.GetHeight() == 400);
}

TEST_CASE("Test Create Image Fail")
{
	REQUIRE_THROWS(Image("path", 10001, 100));
	REQUIRE_THROWS(Image("path", 0, 100));
	REQUIRE_THROWS(Image("path", 100, 10001));
	REQUIRE_THROWS(Image("path", 100, 0));
}

TEST_CASE("Test SetHeight Success")
{
	auto image = Image("path", 300, 400);
	REQUIRE(image.GetHeight() == 400);

	image.SetHeight(10000);
	REQUIRE(image.GetHeight() == 10000);

	image.SetHeight(1);
	REQUIRE(image.GetHeight() == 1);
}

TEST_CASE("Test SetHeight Fail")
{
	auto image = Image("path", 300, 400);
	REQUIRE(image.GetHeight() == 400);

	REQUIRE_THROWS(image.SetHeight(10001));
	REQUIRE_THROWS(image.SetHeight(0));
}

TEST_CASE("Test SetWidth Success")
{
	auto image = Image("path", 300, 400);
	REQUIRE(image.GetWidth() == 300);

	image.SetWidth(10000);
	REQUIRE(image.GetWidth() == 10000);

	image.SetWidth(1);
	REQUIRE(image.GetWidth() == 1);
}

TEST_CASE("Test SetWidth Fail")
{
	auto image = Image("path", 300, 400);

	REQUIRE_THROWS(image.SetWidth(10001));
	REQUIRE_THROWS(image.SetWidth(0));
}