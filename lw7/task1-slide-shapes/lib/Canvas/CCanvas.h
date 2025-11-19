#pragma once

#include "../Common/Color.h"
#include "../Common/Point.h"
#include "./ICanvas.h"
#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

class CCanvas : public ICanvas
{
public:
	void DrawEllipse(float cx, float cy, float rx, float ry) override
	{
		m_canvas += std::format(R"(  <ellipse cx="{}" cy="{}" rx="{}" ry="{}" fill="{}" stroke="{}" stroke-width="{}"/>)", cx, cy, rx, ry, m_fillColor, m_outlineColor, m_thickness) + "\n";
	}

	void DrawLine(float x1, float y1, float x2, float y2) override
	{
		m_canvas += std::format(R"(  <line x1="{}" y1="{}" x2="{}" y2="{}" stroke="{}" stroke-width="{}"/>)", x1, y1, x2, y2, m_outlineColor, m_thickness) + "\n";
	}

	void DrawPolygon(std::vector<Point> points) override
	{
		std::string stringPoints;
		for (auto& point : points)
		{
			stringPoints += std::format("{},{} ", point.x, point.y);
		}

		if (!stringPoints.empty())
		{
			stringPoints.pop_back();
		}

		m_canvas += std::format(R"(  <polygon points="{}" fill="{}" stroke="{}" stroke-width="{}"/>)", stringPoints, m_fillColor, m_outlineColor, m_thickness) + "\n";
	}

	void SetThickness(size_t thickness) override
	{
		m_thickness = thickness;
	}

	void SetFillColor(std::optional<Color> color) override
	{
		m_fillColor = color.has_value()
			? ConvertColorToString(color.value())
			: "#00000000";
	}

	void SetOutlineColor(std::optional<Color> color) override
	{
		m_outlineColor = color.has_value()
			? ConvertColorToString(color.value())
			: "#00000000";
	}

	void SetWidth(size_t width) override
	{
		m_width = width;
	}

	void SetHeight(size_t height) override
	{
		m_height = height;
	}

	void Clear() override
	{
		m_canvas.clear();
		m_fillColor = "#000000";
		m_outlineColor = "#000000";
	}

	void Save(const std::string& fileName)
	{
		std::ofstream file(fileName);
		if (!file.is_open())
		{
			throw std::runtime_error("Cannot open file for writing: " + fileName);
		}

		file << R"(<?xml version="1.0" encoding="UTF-8"?>)" << "\n";
		file << std::format(R"(<svg xmlns="http://www.w3.org/2000/svg" width="{}" height="{}">)", m_width, m_height) << "\n";
		file << m_canvas;
		file << "</svg>" << "\n";
	}

private:
	std::string m_canvas;
	std::string m_outlineColor;
	std::string m_fillColor;
	size_t m_thickness;
	size_t m_width;
	size_t m_height;

	static std::string ConvertColorToString(Color color)
	{
		std::ostringstream oss;
		oss << "#" << std::hex << std::setw(8) << std::setfill('0') << color;

		return oss.str();
	}
};