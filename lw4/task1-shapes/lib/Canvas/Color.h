#pragma once

#include <string>

enum class Color
{
	Red,
	Green,
	Blue,
	Yellow,
	Pink,
	Black,
};

static std::string ColorToString(const Color color)
{
	switch (color)
	{
	case Color::Red:
		return "Red";
	case Color::Green:
		return "Green";
	case Color::Blue:
		return "Blue";
	case Color::Yellow:
		return "Yellow";
	case Color::Pink:
		return "Pink";
	case Color::Black:
		return "Black";
	default:
		return "None";
	}
}