#pragma once

#include "IObservable.h"
#include "IObserver.h"
#include <functional>
#include <map>
#include <set>
#include <unordered_map>

template <class T>
class CPriorityObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		if (m_observersMap.find(&observer) != m_observersMap.end())
		{
			return;
		}

		auto it = m_priorityObservers.emplace(-priority, &observer);
		try
		{
			m_observersMap[&observer] = it;
		}
		catch (...)
		{
			m_priorityObservers.erase(it);
			throw;
		}
	}

	void NotifyObservers() override
	{
		auto observers = GetObserversCopy();
		T data = GetChangedData();
		for (auto& observer : observers)
		{
			observer->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto it = m_observersMap.find(&observer);
		if (it == m_observersMap.end())
		{
			return;
		}

		m_priorityObservers.erase(it->second);
		m_observersMap.erase(it);
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_priorityObservers;
	std::unordered_map<ObserverType*, typename std::multimap<int, ObserverType*>::iterator> m_observersMap;

	std::vector<ObserverType*> GetObserversCopy() const
	{
		std::vector<ObserverType*> observers;
		observers.reserve(m_priorityObservers.size());
		for (const auto& pair : m_priorityObservers)
		{
			observers.push_back(pair.second);
		}
		return observers;
	}
};