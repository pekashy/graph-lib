#include "graph-iterator.h"

#include <stack>
#include <iostream>

namespace
{
	class GraphIteratorImpl : public GraphIterator
	{
	public:
		GraphIteratorImpl(Graph::Ptr pGraph, int StartNodeId);
		GraphVertex::Ptr Next() override;
	private:
		const Graph::Ptr m_pGraph;
		int m_nCurrentPositionId;

		std::stack<int> m_visitPlan;
		std::set<int> m_visited;
	};
}

GraphIteratorImpl::GraphIteratorImpl(Graph::Ptr pGraph, int nStartNodeId)
	: m_pGraph(pGraph)
	, m_nCurrentPositionId(nStartNodeId)
{
	m_visitPlan.push(nStartNodeId);
}

GraphVertex::Ptr GraphIteratorImpl::Next()
{
	if(m_pGraph == nullptr)
	{
		std::cerr << "Iterator is broken, try recreating\n";
		return nullptr;
	}

	if(m_visitPlan.empty())
	{
		return nullptr;
	}

	int newVisitId = m_visitPlan.top();
	m_visitPlan.pop();
	m_visited.insert(newVisitId);

	auto visitingVertex = m_pGraph->GetVertex(newVisitId);
	if(visitingVertex == nullptr)
	{
		return nullptr;
	}

	auto adjacentIndices = m_pGraph->GetAdjacentVertices(newVisitId);
	for(auto& index : adjacentIndices)
	{
		if(m_visited.find(index) == end(m_visited))
		{
			m_visitPlan.push(index);
			m_visited.insert(index);
		}
	}

	return visitingVertex;
}

GraphIterator::Ptr GraphIteratorFactory::CreateGraphIterator(Graph::Ptr pGraph, int nStartNodeId)
{
	return std::make_unique<GraphIteratorImpl>(pGraph, nStartNodeId);
}