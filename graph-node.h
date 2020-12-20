#pragma once

#include <memory>
#include "common.h"

class GraphEdge
{
public:
	virtual ~GraphEdge() = default;
};

template<typename T>
class ConcreteGraphEdge : public GraphEdge
{
public:
	virtual ~ConcreteGraphEdge() = default;

	static std::shared_ptr<GraphEdge> Create(T* pContent) 
	{
		struct make_shared_enabler : public ConcreteGraphEdge<T> 
		{
			make_shared_enabler(T* pC) : ConcreteGraphEdge<T>(pC) {};
		};
		return std::make_shared<make_shared_enabler>(pContent); 
	};

private:
	ConcreteGraphEdge(T* pContent)
		: m_shContent(std::make_shared<T>(*pContent))
	{}

	std::shared_ptr<T> m_shContent;
};

using FunnyGraphEdge = ConcreteGraphEdge<FunnyGraphObject>;