#pragma once

#include "visitors.h"

#include <iostream>
#include <unordered_map>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <functional>

template
<
	class BaseObjectType,
	typename CallbackType = std::function<void(Visitor::Ptr)>
>
class VisitorDispatcher
{
	using MapType = std::unordered_map<std::type_index, CallbackType>;
	MapType callbackMap;
public:
	template <class ConcreteObjectType>
	void add(CallbackType fun)
	{
		callbackMap.emplace(typeid(ConcreteObjectType), fun);
	}

	template <class ConcreteObjectType>
	void remove()
	{
		callbackMap.erase(std::type_index(typeid(ConcreteObjectType)));
	}

	CallbackType Go(std::shared_ptr<BaseObjectType> pUnknownObject)
	{
		std::type_index k(typeid(*pUnknownObject));
		typename MapType::iterator it = callbackMap.find(k);
		if (it == callbackMap.end())
		{
			std::cerr << "Error. Types not found";
		}

		return it->second;
	}
};
