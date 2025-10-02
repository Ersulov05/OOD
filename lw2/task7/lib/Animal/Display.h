#pragma once

#include "./AnimalData.h"
#include <iostream>

class CAnimalDisplay : public IObserver<SAnimalInfo, AnimalEventType>
{
private:
	void Update(SAnimalInfo const& data, AnimalEventType const& eventType) override
	{
		std::cout << "changed " << data.animal << " data" << std::endl;
		switch (eventType)
		{
		case AnimalEventType::ChangeEnergy:
			PrintEnergy(data);
			break;
		case AnimalEventType::ChangeHealth:
			PrintHealth(data);
			break;
		default:
			PrintAllInfo(data);
			break;
		}
		std::cout << "----------------" << std::endl;
	}

	void PrintEnergy(SAnimalInfo const& data) const
	{
		std::cout << "Current Energy: " << data.energy << std::endl;
	}

	void PrintHealth(SAnimalInfo const& data) const
	{
		std::cout << "Current Health: " << data.health << std::endl;
	}

	void PrintAllInfo(SAnimalInfo const& data) const
	{
		PrintHealth(data);
		PrintEnergy(data);
	}
};