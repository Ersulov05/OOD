#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/tile.h"
#include <sstream>

TEST_CASE("Default create Tile")
{
	Tile tile;
	for (int y = 0; y < Tile::SIZE; ++y)
	{
		for (int x = 0; x < Tile::SIZE; ++x)
		{
			REQUIRE(tile.GetPixel({ x, y }) == 0);
		}
	}
}

TEST_CASE("Create Tile with color")
{
	Tile tile('X');
	for (int y = 0; y < Tile::SIZE; ++y)
	{
		for (int x = 0; x < Tile::SIZE; ++x)
		{
			REQUIRE(tile.GetPixel({ x, y }) == 'X');
		}
	}
}

TEST_CASE("SetPixel success")
{
	Tile tile;

	tile.SetPixel({ 0, 0 }, 'A');
	tile.SetPixel({ 7, 7 }, 'B');

	REQUIRE(tile.GetPixel({ 0, 0 }) == 'A');
	REQUIRE(tile.GetPixel({ 7, 7 }) == 'B');
}

TEST_CASE("SetPixel ignores out of bounds")
{
	Tile tile('X');

	tile.SetPixel({ -1, 0 }, 'A');
	tile.SetPixel({ 0, -1 }, 'A');
	tile.SetPixel({ 8, 0 }, 'A');
	tile.SetPixel({ 0, 8 }, 'A');
	tile.SetPixel({ -1, -1 }, 'A');
	tile.SetPixel({ 8, 8 }, 'A');

	for (int y = 0; y < Tile::SIZE; ++y)
	{
		for (int x = 0; x < Tile::SIZE; ++x)
		{
			REQUIRE(tile.GetPixel({ x, y }) == 'X');
		}
	}
}

TEST_CASE("GetPixel returns 0 for out of bounds")
{
	Tile tile('X');

	REQUIRE(tile.GetPixel({ -1, 0 }) == 0);
	REQUIRE(tile.GetPixel({ 0, -1 }) == 0);
	REQUIRE(tile.GetPixel({ 8, 0 }) == 0);
	REQUIRE(tile.GetPixel({ 0, 8 }) == 0);
	REQUIRE(tile.GetPixel({ -1, -1 }) == 0);
	REQUIRE(tile.GetPixel({ 8, 8 }) == 0);
}

TEST_CASE("Copy GetPixel")
{
	Tile original('O');
	original.SetPixel({ 2, 3 }, 'Z');
	original.SetPixel({ 5, 1 }, 'W');

	Tile copy = original;

	for (int y = 0; y < Tile::SIZE; ++y)
	{
		for (int x = 0; x < Tile::SIZE; ++x)
		{
			REQUIRE(copy.GetPixel({ x, y }) == original.GetPixel({ x, y }));
		}
	}

	copy.SetPixel({ 0, 0 }, 'C');
	REQUIRE(original.GetPixel({ 0, 0 }) == 'O');
	REQUIRE(copy.GetPixel({ 0, 0 }) == 'C');
}

TEST_CASE("Instance counting works")
{
	int initialCount = Tile::GetInstanceCount();

	{
		Tile tile1;
		REQUIRE(Tile::GetInstanceCount() == initialCount + 1);

		Tile tile2('X');
		REQUIRE(Tile::GetInstanceCount() == initialCount + 2);

		Tile tile3 = tile2;
		REQUIRE(Tile::GetInstanceCount() == initialCount + 3);
	}

	REQUIRE(Tile::GetInstanceCount() == initialCount);
}
