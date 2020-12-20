#include "graph-lib.h"
#include <iostream>

namespace
{
	class AdjMatrixGraph : public Graph
	{
		void AddEdge(const GraphEdge& edge) override {};
		void PrintTest() override {std::cout << "Test AdjMatrixGraph" << std::endl;};
	};

	class AdjListGraph : public Graph
	{
		void AddEdge(const GraphEdge& edge) override {};
		void PrintTest() override {std::cout << "Test AdjListGraph" << std::endl;};
	};

	class PointerStructGraph : public Graph
	{
		void AddEdge(const GraphEdge& edge) override {};
		void PrintTest() override {std::cout << "Test PointerStructGraph" << std::endl;};
	};
}

std::shared_ptr<Graph> GraphFactory::CreateAdjMatrixGraph()
{
	return std::make_shared<AdjMatrixGraph>();
}

std::shared_ptr<Graph> GraphFactory::CreateAdjListGraph()
{
	return std::make_shared<AdjListGraph>();
}

std::shared_ptr<Graph> GraphFactory::CreatePointerStructGraph()
{
	return std::make_shared<PointerStructGraph>();
}
