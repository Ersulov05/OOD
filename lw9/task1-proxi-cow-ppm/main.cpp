#include <cmath>
#include <iostream>

#include "./lib/drawer.h"
#include "./lib/saver.h"

int main()
{
	Image img{ { 80, 40 }, 0x007f00 };
	DrawCircle(img, { 16, 14 }, 8, 0xffffff);
	DrawCircle(img, { 63, 14 }, 8, 0xffffff);
	FillCircle(img, { 13, 15 }, 3, 0xffffff);
	FillCircle(img, { 60, 15 }, 3, 0xffffff);
	DrawLine(img, { 20, 30 }, { 29, 34 }, 0xffffff);
	DrawLine(img, { 29, 34 }, { 50, 34 }, 0xffffff);
	DrawLine(img, { 50, 34 }, { 59, 30 }, 0xffffff);
	SaveImageToPPM(img, "image");

	{
		Image img{ { 30, 30 }, 0x007f00 };
		FillCircle(img, { 15, 10 }, 4, 0xffffff);
		DrawCircle(img, { 15, 20 }, 4, 0xffffff);
		SaveImageToPPM(img, "test");
	}
}
