#pragma once

#include<utility>

//TODO 
// Set Bind function to pure virtual then creates SubClass SimpleDelegate and MultiDelegate
template<typename RetType, typename... Args>
class DelegateBase
{
	
	typedef void* InstancePtr;
	typedef RetType (*InternalFunction)(InstancePtr, Args&...);

	template<RetType(*Function)(Args&...)>
	static inline RetType FunctionToInternal(InstancePtr, Args&... InArg)
	{
		return (Function)(InArg);
	}

	template<class C, RetType(C::*Function)(Args&...)>
	static inline RetType ClassFunctionToInternal(InstancePtr Instance, Args&... Arg)
	{
		return (static_cast<C*>(Instance)->*Function)(Arg...);
	}

public:
	DelegateBase(void) :
		Callback(nullptr, nullptr)
	{
	}

	RetType Invoke(Args&... Arg) const
	{
		if (Callback.second) {
			return Callback.second(Callback.first, Arg...);
		}
	}

	template<RetType(*Function)(Args&...)>
	void Bind(void)
	{
		Callback.first = nullptr;
		Callback.second = &FunctionToInternal<Function>;
	}

	template<class C, RetType(C::* Function)(Args&...)>
	void Bind(C* Instance)
	{
		Callback.first = Instance;
		Callback.second = &ClassFunctionToInternal<C, Function>;
	}

private:
	std::pair<InstancePtr, InternalFunction> Callback;
};

