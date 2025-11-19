#pragma once

struct Frame
{
	float left;
	float top;
	float width;
	float height;

	Frame(float left, float top, float width, float height)
		: left(left)
		, top(top)
		, width(width)
		, height(height)
	{
		if (width < 1 || height < 1)
		{
			throw std::invalid_argument("invalid frame size");
		}
	}
};