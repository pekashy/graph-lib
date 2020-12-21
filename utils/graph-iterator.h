#pragma once

#include "../lib/graph-lib.h"

class GraphIterator
{
public:
	using Ptr = std::unique_ptr<GraphIterator>;
	virtual GraphVertex::Ptr Next() = 0;
	virtual ~GraphIterator() = default;
};

namespace GraphIteratorFactory
{
	GraphIterator::Ptr CreateGraphIterator(Graph::Ptr pGraph, int StartNodeId);
}
