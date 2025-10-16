#pragma once

#include "../Shape/Point.h"
#include "./Exception/UnknownColorException.h"
#include "./ICanvas.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

class CCanvas : public ICanvas
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

	void DrawEllipse(float cx, float cy, float rx, float ry)
	{
		sf::ConvexShape ellipse;
		const int points = 100;

		ellipse.setFillColor(sf::Color::Transparent);
		ellipse.setOutlineColor(m_color);
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

	void DrawLine(float x1, float y1, float x2, float y2)
	{
		float thickness = 1.0;
		for (float i = -thickness / 2; i <= thickness / 2; i += 0.5f)
		{
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x1 + i, y1 + i), m_color),
				sf::Vertex(sf::Vector2f(x2 + i, y2 + i), m_color)
			};
			m_renderTexture->draw(line, 2, sf::Lines);
		}
	}

	void SetColor(Color color)
	{
		m_color = ConvertColorToSFMLColor(color);
	}

	void RunWindow()
	{
		sf::Sprite textureSprite(m_renderTexture->getTexture());
		sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Canvas");
		while (window.isOpen())
		{
			ProcessEvents(window);
			window.clear(sf::Color::White);
			window.draw(textureSprite);
			window.display();
		}
	}

private:
	u_int32_t m_width;
	u_int32_t m_height;
	std::unique_ptr<sf::RenderTexture> m_renderTexture;
	sf::Color m_color;

	static sf::Color ConvertColorToSFMLColor(Color color)
	{
		switch (color)
		{
		case Color::Red:
			return sf::Color(0xff0000ff);
		case Color::Green:
			return sf::Color(0x00ff00ff);
		case Color::Blue:
			return sf::Color(0x0000ffff);
		case Color::Black:
			return sf::Color(0x000000ff);
		case Color::Yellow:
			return sf::Color(0xffff00ff);
		case Color::Pink:
			return sf::Color(0xff00ffff);
		default:
			throw UnknownColorException();
		}
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
};