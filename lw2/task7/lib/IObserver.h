#pragma once

template <typename ObserverDataType, typename EventType>
class IObserver
{
public:
	virtual void Update(ObserverDataType const& data, EventType const& eventType) = 0;
	virtual ~IObserver() = default;
};