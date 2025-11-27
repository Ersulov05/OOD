#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/image.h"
#include <sstream>

TEST_CASE("Create Image with size and color")
{
	Image img({ 10, 5 }, 'X');
	REQUIRE(img.GetSize().width == 10);
	REQUIRE(img.GetSize().height == 5);
	REQUIRE(Tile::GetInstanceCount() == 1);

	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			REQUIRE(img.GetPixel({ x, y }) == 'X');
		}
	}
	REQUIRE(img.GetPixel({ 10, 5 }) == 0);
	REQUIRE(img.GetPixel({ -1, -1 }) == 0);
}

TEST_CASE("Create Image with size кратным Tile::SIZE")
{
	Image img({ Tile::SIZE, Tile::SIZE }, 'X');
	REQUIRE(img.GetSize().width == 8);
	REQUIRE(img.GetSize().height == 8);
	REQUIRE(Tile::GetInstanceCount() == 1);

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			REQUIRE(img.GetPixel({ x, y }) == 'X');
		}
	}
	REQUIRE(img.GetPixel({ 8, 8 }) == 0);
	REQUIRE(img.GetPixel({ -1, -1 }) == 0);
}

TEST_CASE("Create Image with zero size")
{
	Image img({ 0, 0 }, 'X');
	REQUIRE(img.GetSize().width == 0);
	REQUIRE(img.GetSize().height == 0);
	REQUIRE(Tile::GetInstanceCount() == 0);
}

TEST_CASE("GetPixel returns 0 for out of bounds")
{
	Image img({ 1, 1 }, 'X');

	REQUIRE(img.GetPixel({ -1, 0 }) == 0);
	REQUIRE(img.GetPixel({ 0, -1 }) == 0);
	REQUIRE(img.GetPixel({ 1, 0 }) == 0);
	REQUIRE(img.GetPixel({ 0, 1 }) == 0);
	REQUIRE(img.GetPixel({ -1, -1 }) == 0);
	REQUIRE(img.GetPixel({ 1, 1 }) == 0);
}

TEST_CASE("SetPixel out of bounds")
{
	Image img({ 2, 2 }, 'X');

	img.SetPixel({ -1, 0 }, 'A');
	img.SetPixel({ 0, -1 }, 'A');
	img.SetPixel({ 2, 0 }, 'A');
	img.SetPixel({ 0, 2 }, 'A');
	img.SetPixel({ -1, -1 }, 'A');
	img.SetPixel({ 2, 2 }, 'A');

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			REQUIRE(img.GetPixel({ x, y }) == 'X');
		}
	}

	REQUIRE(Tile::GetInstanceCount() == 1);
}

TEST_CASE("SetPixel one tile")
{
	Image img({ 16, 16 }, 'X');
	REQUIRE(Tile::GetInstanceCount() == 1);

	img.SetPixel({ 0, 0 }, 'A');
	img.SetPixel({ 7, 7 }, 'B');
	REQUIRE(img.GetPixel({ 0, 0 }) == 'A');
	REQUIRE(img.GetPixel({ 7, 7 }) == 'B');

	REQUIRE(Tile::GetInstanceCount() == 2);
}

TEST_CASE("SetPixel two tiles")
{
	Image img({ 16, 16 }, 'X');
	REQUIRE(Tile::GetInstanceCount() == 1);

	img.SetPixel({ 0, 0 }, 'A');
	img.SetPixel({ 7, 7 }, 'B');
	REQUIRE(Tile::GetInstanceCount() == 2);
	img.SetPixel({ 8, 8 }, 'C');
	img.SetPixel({ 15, 15 }, 'D');
	REQUIRE(Tile::GetInstanceCount() == 3);

	REQUIRE(img.GetPixel({ 0, 0 }) == 'A');
	REQUIRE(img.GetPixel({ 7, 7 }) == 'B');
	REQUIRE(img.GetPixel({ 8, 8 }) == 'C');
	REQUIRE(img.GetPixel({ 15, 15 }) == 'D');
}

TEST_CASE("SetPixel all tiles")
{
	Image img({ 16, 16 }, 'X');
	REQUIRE(Tile::GetInstanceCount() == 1);

	img.SetPixel({ 0, 0 }, 'A');
	img.SetPixel({ 7, 7 }, 'B');
	REQUIRE(Tile::GetInstanceCount() == 2);
	img.SetPixel({ 8, 8 }, 'C');
	img.SetPixel({ 15, 15 }, 'D');
	REQUIRE(Tile::GetInstanceCount() == 3);
	img.SetPixel({ 8, 0 }, 'E');
	img.SetPixel({ 15, 7 }, 'F');
	REQUIRE(Tile::GetInstanceCount() == 4);
	img.SetPixel({ 0, 8 }, 'G');
	img.SetPixel({ 7, 15 }, 'H');
	REQUIRE(Tile::GetInstanceCount() == 4);

	REQUIRE(img.GetPixel({ 0, 0 }) == 'A');
	REQUIRE(img.GetPixel({ 7, 7 }) == 'B');
	REQUIRE(img.GetPixel({ 8, 8 }) == 'C');
	REQUIRE(img.GetPixel({ 15, 15 }) == 'D');
	REQUIRE(img.GetPixel({ 8, 0 }) == 'E');
	REQUIRE(img.GetPixel({ 15, 7 }) == 'F');
	REQUIRE(img.GetPixel({ 0, 8 }) == 'G');
	REQUIRE(img.GetPixel({ 7, 15 }) == 'H');
}

TEST_CASE("Print empty image")
{
	Image img({ 0, 0 }, 'X');

	std::stringstream out;

	Print(img, out);
	REQUIRE(out.str() == "");
}

TEST_CASE("Print image")
{
	Image img({ 4, 4 }, 'X');
	img.SetPixel({ 0, 0 }, 'A');
	img.SetPixel({ 1, 1 }, 'B');
	img.SetPixel({ 2, 2 }, 'C');
	img.SetPixel({ 3, 3 }, 'D');

	std::stringstream out;

	Print(img, out);
	REQUIRE(out.str() == "AXXX\nXBXX\nXXCX\nXXXD\n");
}

TEST_CASE("Load empty image")
{
	auto img = LoadImage(
		"AXX\n"
		"XBXT\n");

	REQUIRE(img.GetSize().width == 4);
	REQUIRE(img.GetSize().height == 2);

	REQUIRE(img.GetPixel({ 0, 0 }) == 'A');
	REQUIRE(img.GetPixel({ 1, 0 }) == 'X');
	REQUIRE(img.GetPixel({ 2, 0 }) == 'X');
	REQUIRE(img.GetPixel({ 3, 0 }) == 0);
	REQUIRE(img.GetPixel({ 0, 1 }) == 'X');
	REQUIRE(img.GetPixel({ 1, 1 }) == 'B');
	REQUIRE(img.GetPixel({ 2, 1 }) == 'X');
	REQUIRE(img.GetPixel({ 3, 1 }) == 'T');
}