#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/CriptUtils/CriptUtils.h"
#include "../lib/Stream/Output/CMemoryOutputStream.h"
#include "../lib/Stream/Output/Decorator/CCompressOutputStream.h"

TEST_CASE("Test WriteByte with compressed")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	auto* originalMemoryPtr = memoryOutputStream.get();

	CCompressOutputStream compressOutputStream(std::move(memoryOutputStream));

	compressOutputStream.WriteByte('x');
	compressOutputStream.Close();

	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ 'x', 1 });
}

TEST_CASE("Test multi WriteByte with compressed")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	auto* originalMemoryPtr = memoryOutputStream.get();

	CCompressOutputStream compressOutputStream(std::move(memoryOutputStream));

	compressOutputStream.WriteByte('x');
	compressOutputStream.WriteByte('x');
	compressOutputStream.WriteByte('y');
	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ 'x', 2 });
	compressOutputStream.WriteByte('y');
	compressOutputStream.Close();

	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ 'x', 2, 'y', 2 });
}

TEST_CASE("Test WriteBlock with compressed")
{
	auto memoryOutputStream = std::make_unique<CMemoryOutputStream>();
	auto* originalMemoryPtr = memoryOutputStream.get();

	CCompressOutputStream compressOutputStream(std::move(memoryOutputStream));

	compressOutputStream.WriteBlock("xxxyyyyzz", 9);
	compressOutputStream.Close();

	REQUIRE(originalMemoryPtr->GetBytes() == std::vector<uint8_t>{ 'x', 3, 'y', 4, 'z', 2 });
}
