#pragma once

#include "IObservable.h"
#include "IObserver.h"
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

// TODO Давать понятные имена шаблонным типам
template <class ObserverDataType, class EventType>
class CPriorityObservable : public IObservable<ObserverDataType, EventType>
{
public:
	typedef IObserver<ObserverDataType, EventType> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority, EventType eventType) override
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

	void NotifyObservers(EventType eventType) override
	{
		auto observers = GetObserversForEvent(eventType);
		ObserverDataType data = GetChangedData();
		for (auto& observer : observers)
		{
			observer->Update(data, eventType);
		}
	}

	void RemoveObserver(ObserverType& observer, EventType eventType) override
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
	virtual ObserverDataType GetChangedData() const = 0;

private:
	struct ObserverInfo
	{
		ObserverType* observer;
		EventType eventType;

		bool operator==(const ObserverInfo& other) const
		{
			return observer == other.observer && eventType == other.eventType;
		}
	};

	struct ObserverInfoHash
	{
		std::size_t operator()(const ObserverInfo& info) const
		{
			// не привязываться к инту
			return std::hash<ObserverType*>()(info.observer) * 41 + std::hash<EventType>()(info.eventType);
		}
	};

	std::multimap<int, ObserverInfo> m_priorityObservers;
	std::unordered_map<ObserverInfo, typename std::multimap<int, ObserverInfo>::iterator, ObserverInfoHash> m_observersMap;

	std::vector<ObserverType*> GetObserversForEvent(EventType eventType) const
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