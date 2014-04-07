// Profiler.h 

#pragma once

#include "core/Delegate.h"
#include <string>
#include <vector>


struct CounterInfo
{
	std::string id;
	std::string title;
};

class CounterBase
{
public:
	CounterBase(const std::string &id, const std::string &title);
	void Push(float value);

	static size_t GetMarkerCountStatic();
	static const CounterInfo& GetMarkerInfoStatic(size_t idx);
	static void SetMarkerCallbackStatic(size_t idx, const Delegate<void(float)> &cb);

private:
	Delegate<void(float)> _callback;

	struct CounterInfoEx : public CounterInfo
	{
		CounterInfoEx(const CounterInfo &src): CounterInfo(src) {}
		CounterBase *ptr;
	};

	static size_t RegisterMarkerStatic(const CounterInfo &info, CounterBase *ptr);
	static std::vector<CounterInfoEx>& GetRegisteredCountersStatic();
};

// end of file
