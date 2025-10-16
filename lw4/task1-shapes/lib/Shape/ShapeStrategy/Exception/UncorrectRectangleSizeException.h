#pragma once
#include <iostream>

class UncorrectRectangleSizeException : public std::invalid_argument
{
public:
	UncorrectRectangleSizeException()
		: std::invalid_argument("Uncorrect rectangle size"){};
};