#include "./lib/CCanvasPainter.h"

int main()
{
	std::cout << "Should we use new API (y)?";
	std::string userInput;
	if (getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphics();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	return 0;
}
