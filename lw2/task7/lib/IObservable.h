#pragma once

#include "IObserver.h"

template <typename T1, typename T2>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T1, T2>& observer, int priority, T2 eventType) = 0;
	virtual void NotifyObservers(T2 eventType) = 0;
	virtual void RemoveObserver(IObserver<T1, T2>& observer, T2 eventType) = 0;
};
