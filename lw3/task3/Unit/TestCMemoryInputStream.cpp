#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/Input/CMemoryInputStream.h"

TEST_CASE("Test IsEOF")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 1, 2, 3, 4, 5, 6 });

	REQUIRE(memoryInputStream.IsEOF() == false);
}

TEST_CASE("Test IsEOF Empty")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{});

	REQUIRE(memoryInputStream.IsEOF() == true);
}

TEST_CASE("Test IsEOF Close")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{});
	memoryInputStream.Close();
	REQUIRE_THROWS(memoryInputStream.IsEOF());
}

TEST_CASE("Test ReadByte Empty")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{});
	REQUIRE_THROWS(memoryInputStream.ReadByte());
}

TEST_CASE("Test ReadByte Close")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 1, 2 });
	memoryInputStream.Close();
	REQUIRE_THROWS(memoryInputStream.ReadByte());
}

TEST_CASE("Test ReadByte")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 1, 2 });
	auto byte = memoryInputStream.ReadByte();
	REQUIRE(byte == 1);
}

TEST_CASE("Test ReadBlock")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 'x', 'y', 'z', 'a', 'b' });

	char bytes[6] = {};

	memoryInputStream.ReadBlock(bytes, 5);

	REQUIRE(std::string(bytes) == "xyzab");
}

TEST_CASE("Test ReadBlock Zero")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 'x', 'y', 'z', 'a', 'b' });

	char bytes[6] = {};

	memoryInputStream.ReadBlock(bytes, 0);

	REQUIRE(std::string(bytes) == "");
}

TEST_CASE("Test ReadBlock Close")
{
	CMemoryInputStream memoryInputStream(std::vector<uint8_t>{ 'x', 'y', 'z', 'a', 'b' });
	memoryInputStream.Close();
	char bytes[6] = {};

	REQUIRE_THROWS(memoryInputStream.ReadBlock(bytes, 5));
}
