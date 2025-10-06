#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(bool isDouble = false)
		: CCoffee(isDouble ? "Double Cappuccino" : "Cappuccino")
		, m_isDouble(isDouble)
	{
	}

	double GetCost() const override
	{
		return m_isDouble ? 120 : 80;
	}

private:
	bool m_isDouble;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(bool isDouble = false)
		: CCoffee(isDouble ? "Double Latte" : "Latte")
		, m_isDouble(isDouble)
	{
	}

	double GetCost() const override
	{
		return m_isDouble ? 130 : 90;
	}

private:
	bool m_isDouble;
};

enum class TeaType
{
	Black,
	Green,
	Red,
	White
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType teaType = TeaType::Black)
		: CBeverage(GetTeaTypeName(teaType) + " tea")
	{
	}

	double GetCost() const override
	{
		return 30;
	}

private:
	static std::string GetTeaTypeName(TeaType teaType)
	{
		switch (teaType)
		{
		case TeaType::Black:
			return "Black";
		case TeaType::Green:
			return "Green";
		case TeaType::Red:
			return "Red";
		case TeaType::White:
			return "White";
		default:
			throw std::runtime_error("Unknown TeaType");
		}
	}
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Large
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size = MilkshakeSize::Large)
		: CBeverage(GetMilkshakeSizeName(size) + " milkshake")
		, m_size(size)
	{
	}

	double GetCost() const override
	{
		return GetMilkshakeSizeCost(m_size);
	}

private:
	MilkshakeSize m_size;

	static std::string GetMilkshakeSizeName(MilkshakeSize size)
	{
		switch (size)
		{
		case MilkshakeSize::Small:
			return "Small";
		case MilkshakeSize::Medium:
			return "Medium";
		case MilkshakeSize::Large:
			return "Large";
		default:
			throw std::runtime_error("Unknown Milkshake size");
		}
	}

	static double GetMilkshakeSizeCost(MilkshakeSize size)
	{
		switch (size)
		{
		case MilkshakeSize::Small:
			return 50;
		case MilkshakeSize::Medium:
			return 60;
		case MilkshakeSize::Large:
			return 80;
		default:
			throw std::runtime_error("Unknown Milkshake size");
		}
	}
};
