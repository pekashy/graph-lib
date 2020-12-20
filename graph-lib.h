#pragma once
#include "graph-node.h"
#include <memory>
#include <set>

class Graph
{
public:
	using AdjStorageType = std::set<int>;

	virtual void AddVertex(GraphVertex::Ptr shVertex) = 0;
	virtual bool AddEdge(const GraphEdge& edge) = 0;
	virtual GraphVertex::Ptr GetVertex(int Id) const = 0;
	virtual const AdjStorageType& GetAdjacentVertices(int Id) = 0;
	virtual void PrintTest() = 0;
	virtual ~Graph() = default;
protected:
	Graph() = default;
};

namespace GraphFactory
{
	std::shared_ptr<Graph> CreateAdjMatrixGraph(); // TBD
	std::shared_ptr<Graph> CreateAdjListGraph();
	std::shared_ptr<Graph> CreatePointerStructGraph(); // TBD
};
