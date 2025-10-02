#pragma once

#include "IObservable.h"
#include "IObserver.h"
#include <functional>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <class T1, class T2>
class CPriorityObservable : public IObservable<T1, T2>
{
public:
	static_assert(std::is_enum_v<T2>, "T2 must be an enum type!");

	typedef IObserver<T1, T2> ObserverType;

	struct ObserverInfo
	{
		ObserverType* observer;
		T2 eventType;

		bool operator==(const ObserverInfo& other) const
		{
			return observer == other.observer && eventType == other.eventType;
		}
	};

	struct ObserverInfoHash
	{
		std::size_t operator()(const ObserverInfo& info) const
		{
			return std::hash<ObserverType*>()(info.observer) ^ std::hash<int>()(static_cast<int>(info.eventType));
		}
	};

	void RegisterObserver(ObserverType& observer, int priority, T2 eventType) override
	{
		ObserverInfo info{ &observer, eventType };

		if (m_observersMap.find(info) != m_observersMap.end())
		{
			return;
		}

		auto it = m_priorityObservers.emplace(-priority, info);
		try
		{
			m_observersMap[info] = it;
		}
		catch (...)
		{
			m_priorityObservers.erase(it);
			throw;
		}
	}

	void NotifyObservers(T2 eventType) override
	{
		auto observers = GetObserversForEvent(eventType);
		T1 data = GetChangedData();
		for (auto& observer : observers)
		{
			observer->Update(data, eventType);
		}
	}

	void RemoveObserver(ObserverType& observer, T2 eventType) override
	{
		ObserverInfo info{ &observer, eventType };
		auto it = m_observersMap.find(info);
		if (it == m_observersMap.end())
		{
			return;
		}

		m_priorityObservers.erase(it->second);
		m_observersMap.erase(it);
	}

protected:
	virtual T1 GetChangedData() const = 0;

private:
	std::multimap<int, ObserverInfo> m_priorityObservers;
	std::unordered_map<ObserverInfo, typename std::multimap<int, ObserverInfo>::iterator, ObserverInfoHash> m_observersMap;

	std::vector<ObserverType*> GetObserversForEvent(T2 eventType) const
	{
		std::vector<ObserverType*> observers;

		for (const auto& [priority, info] : m_priorityObservers)
		{
			if (info.eventType == eventType)
			{
				observers.push_back(info.observer);
			}
		}

		return observers;
	}
};