#pragma once

#include <math.h>
#include <string>

double ToRadians(double degrees)
{
	return degrees * M_PI / 180.0;
}

double ToDegrees(double radians)
{
	return radians * 180.0 / M_PI;
}

double NormalizeAngle(double degrees)
{
	while (degrees >= 360)
		degrees -= 360;
	while (degrees < 0)
		degrees += 360;
	return degrees;
}

std::string DirectionToCardinal(double degrees)
{
	degrees = NormalizeAngle(degrees);

	if (degrees >= 22.5 && degrees < 67.5)
		return "NE";
	if (degrees >= 67.5 && degrees < 112.5)
		return "E";
	if (degrees >= 112.5 && degrees < 157.5)
		return "SE";
	if (degrees >= 157.5 && degrees < 202.5)
		return "S";
	if (degrees >= 202.5 && degrees < 247.5)
		return "SW";
	if (degrees >= 247.5 && degrees < 292.5)
		return "W";
	if (degrees >= 292.5 && degrees < 337.5)
		return "NW";

	return "N";
}
