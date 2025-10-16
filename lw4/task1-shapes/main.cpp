#include "./lib/Canvas/CCanvas.h"
#include "./lib/Client/Client.h"
#include "./lib/Designer/Designer.h"
#include "./lib/Painter/Painter.h"

int main()
{
	auto painter = Painter();
	auto designer = Designer();
	auto client = Client(designer);

	client.Handle(std::cin, painter);

	return 0;
}