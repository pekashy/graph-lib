#pragma once

#include <memory>
#include "common.h"
#include <sstream>

class GraphEdge
{
public:
	virtual ~GraphEdge() = default;
	virtual int GetSource() const = 0;
	virtual int GetDest() const = 0;
};

template<typename T>
class ConcreteGraphEdge : public GraphEdge
{
public:
	virtual ~ConcreteGraphEdge() = default;

	int GetSource() const override
	{
		return m_nSource;
	}

	int GetDest() const override
	{
		return m_nDest;
	}

	static std::shared_ptr<GraphEdge> Create(T* pContent, int nSource, int nDest) 
	{
		struct make_shared_enabler : public ConcreteGraphEdge<T> 
		{
			make_shared_enabler(T* pC, int nS, int nD) : ConcreteGraphEdge<T>(pC, nS, nD) {};
		};
		return std::make_shared<make_shared_enabler>(pContent, nSource, nDest);
	};

private:
	ConcreteGraphEdge(T* pContent, int nSource, int nDest)
		: m_shContent(std::make_shared<T>(*pContent))
		, m_nSource(nSource)
		, m_nDest(nDest)
	{}

	int m_nSource;
	int m_nDest;
	std::shared_ptr<T> m_shContent;
};

using FunnyGraphEdge = ConcreteGraphEdge<FunnyGraphObject>;