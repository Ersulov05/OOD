#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/CriptUtils/CriptUtils.h"
#include "../lib/Stream/Input/CMemoryInputStream.h"
#include "../lib/Stream/Input/Decorator/CDecryptInputStream.h"

TEST_CASE("Test ReadByte with decryption")
{
	uint8_t key = 42;
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ CryptByte('x', key) });

	CDecryptInputStream decryptInputStream(std::move(memoryInputStream), key);

	auto byte = decryptInputStream.ReadByte();

	REQUIRE(byte == 'x');
}

TEST_CASE("Test ReadBlock with decryption")
{
	uint8_t key = 42;
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ CryptByte('x', key), CryptByte('x', key), CryptByte('x', key) });

	CDecryptInputStream decryptInputStream(std::move(memoryInputStream), key);
	char bytes[4] = {};

	decryptInputStream.ReadBlock(bytes, 3);

	REQUIRE(std::string(bytes) == "xxx");
}

TEST_CASE("Test Close ReadByte with decryption")
{
	uint8_t key = 42;
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ CryptByte('x', key) });

	CDecryptInputStream decryptInputStream(std::move(memoryInputStream), key);
	decryptInputStream.Close();

	REQUIRE_THROWS(decryptInputStream.ReadByte());
}

TEST_CASE("Test Close ReadBlock with decryption")
{
	uint8_t key = 42;
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{ CryptByte('x', key), CryptByte('x', key), CryptByte('x', key) });

	CDecryptInputStream decryptInputStream(std::move(memoryInputStream), key);
	decryptInputStream.Close();
	char bytes[4] = {};

	REQUIRE_THROWS(decryptInputStream.ReadBlock(bytes, 3));
}

TEST_CASE("Test Empty ReadByte with decryption")
{
	uint8_t key = 42;
	auto memoryInputStream = std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{});

	CDecryptInputStream decryptInputStream(std::move(memoryInputStream), key);

	REQUIRE_THROWS(decryptInputStream.ReadByte());
}