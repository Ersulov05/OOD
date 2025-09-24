#pragma once

#include "IObservable.h"
#include "IObserver.h"
#include <functional>
#include <set>

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
	}

	void NotifyObservers() override
	{
		auto observers = GetObserversCopy();
		T data = GetChangedData();
		for (auto& observer : observers)
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;

	std::vector<ObserverType*> GetObserversCopy() const
	{
		return std::vector<ObserverType*>(m_observers.begin(), m_observers.end());
	}
};