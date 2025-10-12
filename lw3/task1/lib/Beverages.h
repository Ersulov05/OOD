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

enum class CoffeeSize
{
	STANDART,
	DOUBLE,
}

class CCoffeeWithSize : public CCoffee
{
public:
	CCoffeeWithSize(
		const std::string& description = "Coffee",
		CoffeeSize size = CoffeeSize::STANDART)
		: CCoffee(GetDescription(size, description))
	{
	}

private:
	static std::string GetDescription(CoffeeSize size, std::string description)
	{
		switch (size)
		{
		case CoffeeSize::STANDART:
			return description;
		case CoffeeSize::DOUBLE:
			return "Double " + description;
		default:
			throw std::runtime_error("Unknown Size");
		}
	}
}

// Капуччино
class CCappuccino : public CCoffeeWithSize
{
public:
	CCappuccino(CoffeeSize size = CoffeeSize::STANDART)
		: CCoffeeWithSize("Cappuccino", size) // Избавиться от дублирования
		, m_size(size)
	{
	}

	double GetCost() const override
	{
		return GetSizeCost(m_size);
	}

private:
	CoffeeSize m_size;

	static double GetSizeCost(CoffeeSize size)
	{
		switch (size)
		{
		case CoffeeSize::STANDART:
			return 80;
		case CoffeeSize::DOUBLE:
			return 120;
		default:
			throw std::runtime_error("Unknown size");
		}
	}
};

// Латте
class CLatte : public CCoffeeWithSize
{
public:
	CLatte(CoffeeSize size = CoffeeSize::STANDART)
		: CCoffeeWithSize("Latte", size)
		, m_size(size)
	{
	}

	double GetCost() const override
	{
		return GetSizeCost(m_size);
	}

private:
	CoffeeSize m_size;

	static double GetSizeCost(CoffeeSize size)
	{
		switch (size)
		{
		case CoffeeSize::STANDART:
			return 90;
		case CoffeeSize::DOUBLE:
			return 130;
		default:
			throw std::runtime_error("Unknown size");
		}
	}
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
