#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/CriptUtils/CriptUtils.h"
#include "../lib/Stream/Output/CMemoryOutputStream.h"
#include "../lib/Stream/Output/Decorator/CEncryptOutputStream.h"

TEST_CASE("Test WriteByte with encryption")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	auto* originalMemoryPtr = memoryOutputStream.get();

	uint8_t key = 42;
	CEncryptOutputStream encryptOutputStream(std::move(memoryOutputStream), key);

	encryptOutputStream.WriteByte('x');

	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ CryptByte('x', key) });
}

TEST_CASE("Test WriteBlock with encryption")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	auto* originalMemoryPtr = memoryOutputStream.get();

	uint8_t key = 40;
	CEncryptOutputStream encryptOutputStream(std::move(memoryOutputStream), key);

	encryptOutputStream.WriteBlock("xxx", 3);

	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ CryptByte('x', key), CryptByte('x', key), CryptByte('x', key) });
}

TEST_CASE("Test Close WriteByte with encryption")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();

	uint8_t key = 42;
	CEncryptOutputStream encryptOutputStream(std::move(memoryOutputStream), key);

	encryptOutputStream.Close();
	REQUIRE_THROWS(encryptOutputStream.WriteByte('x'));
}

TEST_CASE("Test Close WriteBlock with encryption")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	uint8_t key = 40;
	CEncryptOutputStream encryptOutputStream(std::move(memoryOutputStream), key);

	encryptOutputStream.Close();
	REQUIRE_THROWS(encryptOutputStream.WriteBlock("xxx", 3));
}
