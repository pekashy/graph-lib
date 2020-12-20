#pragma once

#include <memory>
#include "common.h"
#include <sstream>

class GraphVertex
{
public:
	using Ptr = std::shared_ptr<GraphVertex>;
	virtual ~GraphVertex() = default;
	virtual int GetId() const = 0;
};

template<typename T>
class ConcreteGraphVertex : public GraphVertex
{
public:
	virtual ~ConcreteGraphVertex() = default;

	int GetId() const override
	{
		return m_nId;
	}

	static std::shared_ptr<GraphVertex> Create(T* pContent, int nId) 
	{
		struct make_shared_enabler : public ConcreteGraphVertex<T> 
		{
			make_shared_enabler(T* pC, int nI) : ConcreteGraphVertex<T>(pC, nI) {};
		};
		return std::make_shared<make_shared_enabler>(pContent, nId);
	};

private:
	ConcreteGraphVertex(T* pContent, int nId)
		: m_shContent(std::make_shared<T>(*pContent))
		, m_nId(nId)
	{}

	int m_nId;
	std::shared_ptr<T> m_shContent;
};

struct GraphEdge
{
	GraphEdge(int nSource, int nDest)
		: m_nSource(nSource)
		, m_nDest(nDest)
	{}

	GraphEdge(GraphVertex::Ptr shSource, GraphVertex::Ptr shDest)
		: GraphEdge(shSource->GetId(), shDest->GetId())
	{}

	int m_nSource;
	int m_nDest;
};

using FunnyGraphVertex = ConcreteGraphVertex<FunnyObject>;