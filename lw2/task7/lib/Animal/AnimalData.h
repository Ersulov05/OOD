#pragma once

#include "../Observer.h"
#include <algorithm>
#include <string>
#include <vector>

struct SAnimalInfo
{
	std::string animal;
	int health;
	int energy;
};

enum class AnimalEventType
{
	ChangeHealth,
	ChangeEnergy
};

namespace std
{
template <>
struct hash<AnimalEventType>
{
	size_t operator()(AnimalEventType et) const noexcept
	{
		return hash<underlying_type_t<AnimalEventType>>{}(static_cast<underlying_type_t<AnimalEventType>>(et));
	}
};
} // namespace std

class CAnimalData : public CPriorityObservable<SAnimalInfo, AnimalEventType>
{
public:
	CAnimalData(const std::string& animal)
		: m_animal(animal)
	{
	}

	std::string GetAnimal() const
	{
		return m_animal;
	}

	int GetHealth() const
	{
		return m_health;
	}

	int GetEnergy() const
	{
		return m_energy;
	}

	void SetHealth(int health)
	{
		m_health = health;

		NotifyObservers(AnimalEventType::ChangeHealth);
	}

	void SetEnergy(int energy)
	{
		m_energy = energy;

		NotifyObservers(AnimalEventType::ChangeEnergy);
	}

protected:
	SAnimalInfo GetChangedData() const override
	{
		SAnimalInfo info;
		info.animal = GetAnimal();
		info.health = GetHealth();
		info.energy = GetEnergy();

		return info;
	}

private:
	int m_health = 100;
	int m_energy = 100;
	std::string m_animal;
};