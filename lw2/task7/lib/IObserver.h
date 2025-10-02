#pragma once

template <typename T1, typename T2>
class IObserver
{
public:
	virtual void Update(T1 const& data, T2 const& eventType) = 0;
	virtual ~IObserver() = default;
};