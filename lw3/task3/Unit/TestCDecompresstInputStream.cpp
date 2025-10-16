#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/CriptUtils/CriptUtils.h"
#include "../lib/Stream/Input/CMemoryInputStream.h"
#include "../lib/Stream/Input/Decorator/CDecompressInputStream.h"

TEST_CASE("Test ReadByte with decompressed")
{
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ 'x', 2 });

	CDecompressInputStream decompressInputStream(std::move(memoryInputStream));

	auto byte = decompressInputStream.ReadByte();

	REQUIRE(byte == 'x');
}

TEST_CASE("Test ReadByte with decompressed One Byte")
{
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ 'x' });

	CDecompressInputStream decompressInputStream(std::move(memoryInputStream));

	auto byte = decompressInputStream.ReadByte();

	REQUIRE(byte == 'x');
}

TEST_CASE("Test Empty ReadByte with decompressed")
{
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{});

	CDecompressInputStream decompressInputStream(std::move(memoryInputStream));

	auto byte = decompressInputStream.ReadByte();
	REQUIRE(byte == 0);
}

TEST_CASE("Test Close ReadByte with decompressed")
{
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ 'x' });

	CDecompressInputStream decompressInputStream(std::move(memoryInputStream));
	decompressInputStream.Close();
	REQUIRE_THROWS(decompressInputStream.ReadByte());
}

TEST_CASE("Test ReadBlock with decryption")
{
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ 'x', 30, 'y', 3 });

	CDecompressInputStream decompressInputStream(std::move(memoryInputStream));
	char bytes[50] = {};

	decompressInputStream.ReadBlock(bytes, 32);

	REQUIRE(std::string(bytes) == "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxyy");
}