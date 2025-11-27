#include <cmath>
#include <iostream>

#include "./lib/drawer.h"

constexpr int STAR_COUNT = 20;

int main()
{
	{
		Image img{ { 30, 30 }, '.' };
		FillCircle(img, { 15, 15 }, 4, '#');

		Print(img, std::cout);
	}

	{
		Image img{ { 80, 40 }, '.' };
		DrawCircle(img, { 16, 14 }, 8, '#');
		DrawCircle(img, { 63, 14 }, 8, '#');
		FillCircle(img, { 13, 15 }, 3, '#');
		FillCircle(img, { 60, 15 }, 3, '#');
		DrawLine(img, { 20, 30 }, { 29, 34 }, '#');
		DrawLine(img, { 29, 34 }, { 50, 34 }, '#');
		DrawLine(img, { 50, 34 }, { 59, 30 }, '#');
		Print(img, std::cout);
	}
}
