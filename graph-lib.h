#pragma once

#include "graph-node.h"

#include <memory>

class Graph
{
public:
	virtual void AddVertex(GraphVertex::Ptr shVertex) = 0;
	virtual bool AddEdge(const GraphEdge& edge) = 0;
	virtual void PrintTest() = 0;
	virtual ~Graph() = default;
protected:
	Graph() = default;
};

namespace GraphFactory
{
	std::shared_ptr<Graph> CreateAdjMatrixGraph();
	std::shared_ptr<Graph> CreateAdjListGraph();
	std::shared_ptr<Graph> CreatePointerStructGraph();
};
