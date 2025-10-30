#pragma once
#include <iomanip>
#include <iostream>
#include <memory>

namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	virtual void SetColor(uint32_t rgbColor) = 0;
	// Ставит "перо" в точку x, y
	virtual void MoveTo(int x, int y) = 0;
	// Рисует линию с текущей позиции, передвигая перо в точку x,y
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		std::cout << "SetColor (#" << std::hex << std::setfill('0') << rgbColor << std::dec << ")" << std::endl;
	}

	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
} // namespace graphics_lib
