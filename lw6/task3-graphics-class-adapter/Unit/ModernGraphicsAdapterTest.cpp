#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../lib/ModernGraphicsAdapter.h"
#include <sstream>
#include <string>

TEST_CASE("Test BeginDraw ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();

	std::string outputStr = "<draw>\n";
	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test double BeginDraw ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();

	std::string outputStr = "<draw>\n";
	REQUIRE(out.str() == outputStr);

	REQUIRE_THROWS(modernGraphicsAdapter.BeginDraw());
}

TEST_CASE("Test EndDraw after BeginDraw ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>\n"
							"</draw>\n";
	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test only EndDraw ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	REQUIRE_THROWS(modernGraphicsAdapter.EndDraw());
}

TEST_CASE("Test LineTo ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>"
							"\n  <line fromX=\"0\" fromY=\"0\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n</draw>\n";

	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test MoveTo LineTo ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.MoveTo(200, 200);
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>"
							"\n  <line fromX=\"200\" fromY=\"200\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n</draw>\n";

	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test Multi LineTo ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.LineTo(200, 200);
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>"
							"\n  <line fromX=\"0\" fromY=\"0\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n  <line fromX=\"100\" fromY=\"100\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n  <line fromX=\"100\" fromY=\"100\" toX=\"200\" toY=\"200\">"
							"\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n</draw>\n";

	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test SetColor Line ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.SetColor(0xff0000);
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>"
							"\n  <line fromX=\"0\" fromY=\"0\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"1\" g=\"0\" b=\"0\" a=\"0\" />"
							"\n  </line>"
							"\n</draw>\n";

	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test float SetColor Line ModernGraphicsAdapter")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	modernGraphicsAdapter.BeginDraw();
	modernGraphicsAdapter.SetColor(0x33333333);
	modernGraphicsAdapter.LineTo(100, 100);
	modernGraphicsAdapter.EndDraw();

	std::string outputStr = "<draw>"
							"\n  <line fromX=\"0\" fromY=\"0\" toX=\"100\" toY=\"100\">"
							"\n    <color r=\"0.2\" g=\"0.2\" b=\"0.2\" a=\"0.2\" />"
							"\n  </line>"
							"\n</draw>\n";

	REQUIRE(out.str() == outputStr);
}

TEST_CASE("Test SetColor Line ModernGraphicsAdapter without BeginDraw")
{
	std::stringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsAdapter modernGraphicsAdapter = ModernGraphicsAdapter(renderer);

	REQUIRE_NOTHROW(modernGraphicsAdapter.SetColor(0xff0000));
	REQUIRE_THROWS(modernGraphicsAdapter.LineTo(100, 100));
}