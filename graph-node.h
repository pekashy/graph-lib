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

template<typename TConcrete, typename TBase>
class ConcreteGraphVertex : public GraphVertex
{
public:
	virtual ~ConcreteGraphVertex() = default;

	int GetId() const override
	{
		return m_nId;
	}

	static std::shared_ptr<GraphVertex> Create(TConcrete* pContent, int nId) 
	{
		struct make_shared_enabler : public ConcreteGraphVertex<TConcrete, TBase> 
		{
			make_shared_enabler(TConcrete* pC, int nI) : ConcreteGraphVertex<TConcrete, TBase>(pC, nI) {};
		};
		return std::make_shared<make_shared_enabler>(pContent, nId);
	};

private:
	ConcreteGraphVertex(TConcrete* pContent, int nId)
		: m_shContent(std::make_shared<TConcrete>(*pContent))
		, m_nId(nId)
	{}

	int m_nId;
	std::shared_ptr<TBase> m_shContent;
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
