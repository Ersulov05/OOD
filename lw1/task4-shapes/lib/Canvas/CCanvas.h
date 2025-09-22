#pragma once

#include "../Shape/Point.h"
#include "./ICanvas.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

namespace gfx
{
class CCanvas : public gfx::ICanvas
{
public:
	CCanvas(u_int32_t width, u_int32_t height)
		: m_width(width)
		, m_height(height)
	{
		m_renderTexture = std::make_unique<sf::RenderTexture>();
		if (!m_renderTexture->create(width, height))
		{
			throw std::runtime_error("Failed create render texture");
		}
	}

	void MoveTo(double x, double y)
	{
		m_cursor.x = x;
		m_cursor.y = y;
	}

	void LineTo(double x, double y)
	{
		sf::Vertex line[] = {
			sf::Vertex(
				sf::Vector2f(m_cursor.x, m_cursor.y),
				sf::Color(m_color)),
			sf::Vertex(
				sf::Vector2f(x, y),
				sf::Color(m_color))
		};

		m_renderTexture->draw(line, 2, sf::Lines);

		m_cursor.x = x;
		m_cursor.y = y;
	}

	void DrawEllipse(float cx, float cy, float rx, float ry)
	{
		sf::ConvexShape ellipse;
		const int points = 100;

		ellipse.setFillColor(sf::Color::Transparent);
		ellipse.setOutlineColor(sf::Color(m_color));
		ellipse.setOutlineThickness(2);
		ellipse.setPointCount(points);
		for (int i = 0; i < points; ++i)
		{
			double angle = 2 * M_PI * i / points;
			double x = cx + rx * cos(angle);
			double y = cy + ry * sin(angle);
			ellipse.setPoint(i, sf::Vector2f(x, y));
		}

		m_renderTexture->draw(ellipse);
	}

	void DrawText(double left, double top, double fontSize, const std::string& text)
	{
		sf::Font font;
		font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
		sf::Text txt(text, font, fontSize);
		txt.setPosition(left, top);
		txt.setFillColor(sf::Color(m_color));

		m_renderTexture->draw(txt);
	}

	void SetColor(Color color)
	{
		m_color = color << 8 | 0xff;
	}

	void ProcessEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void RunWindow()
	{
		sf::Sprite textureSprite(m_renderTexture->getTexture());
		sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Canvas");
		while (window.isOpen())
		{
			ProcessEvents(window);
			window.clear(sf::Color::Black);
			window.draw(textureSprite);
			window.display();
		}
	}

private:
	u_int32_t m_width;
	u_int32_t m_height;
	std::unique_ptr<sf::RenderTexture> m_renderTexture;
	Point m_cursor;
	Color m_color;
};
} // namespace gfx