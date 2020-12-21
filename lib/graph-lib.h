#pragma once
#include "graph-node.h"
#include <memory>
#include <set>

class Graph
{
public:
	using AdjStorageType = std::set<int>;
	using Ptr = std::shared_ptr<Graph>;

	virtual void AddVertex(GraphVertex::Ptr shVertex) = 0;
	virtual bool AddEdge(const GraphEdge& edge) = 0;
	virtual GraphVertex::Ptr GetVertex(int Id) const = 0;
	virtual const AdjStorageType& GetAdjacentVertices(int Id) = 0;
	virtual ~Graph() = default;
protected:
	Graph() = default;
};

namespace GraphFactory
{
	Graph::Ptr CreateAdjMatrixGraph();
	Graph::Ptr CreateAdjListGraph();
	Graph::Ptr CreatePointerStructGraph();
};
