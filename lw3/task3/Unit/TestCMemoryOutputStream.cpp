#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/Stream/Output/CMemoryOutputStream.h"

TEST_CASE("Test WriteByte")
{
	CMemoryOutputStream memoryOutputStream;

	memoryOutputStream.WriteByte('x');

	REQUIRE(memoryOutputStream.GetBytes() == std::vector<uint8_t>{ 'x' });
}

TEST_CASE("Test Close WriteByte")
{
	CMemoryOutputStream memoryOutputStream;
	memoryOutputStream.Close();

	REQUIRE_THROWS(memoryOutputStream.WriteByte('x'));
}

TEST_CASE("Test WriteBlock")
{
	CMemoryOutputStream memoryOutputStream;

	memoryOutputStream.WriteBlock("xxx", 3);

	REQUIRE(memoryOutputStream.GetBytes() == std::vector<uint8_t>{ 'x', 'x', 'x' });
}

TEST_CASE("Test WriteBlock Zero")
{
	CMemoryOutputStream memoryOutputStream;

	memoryOutputStream.WriteBlock("xxx", 0);

	REQUIRE(memoryOutputStream.GetBytes() == std::vector<uint8_t>{});
}

TEST_CASE("Test WriteBlock Grete")
{
	CMemoryOutputStream memoryOutputStream;

	memoryOutputStream.WriteBlock("xxx", 5);

	REQUIRE(memoryOutputStream.GetBytes() == std::vector<uint8_t>{ 'x', 'x', 'x' });
}

TEST_CASE("Test Close WriteBlock")
{
	CMemoryOutputStream memoryOutputStream;

	memoryOutputStream.Close();
	REQUIRE_THROWS(memoryOutputStream.WriteBlock("xxx", 3));
}
