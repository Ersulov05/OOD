#pragma once

#include "IObserver.h"

template <typename ObserverDataType, typename EventType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<ObserverDataType, EventType>& observer, int priority, EventType eventType) = 0;
	virtual void NotifyObservers(EventType eventType) = 0;
	virtual void RemoveObserver(IObserver<ObserverDataType, EventType>& observer, EventType eventType) = 0;
};
