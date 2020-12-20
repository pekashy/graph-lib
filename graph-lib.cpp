#include "graph-lib.h"
#include <iostream>
#include <unordered_map>
#include <list>

namespace
{
	class AdjMatrixGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override {};
		bool AddEdge(const GraphEdge& edge) override {};
		void PrintTest() override {std::cout << "Test AdjMatrixGraph" << std::endl;};
	};

	class AdjListGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override;
		bool AddEdge(const GraphEdge& edge) override;
		void PrintTest() override {std::cout << "Test AdjListGraph" << std::endl;};
	private:
		std::unordered_map<int, std::list<int>> m_adjList;
		std::unordered_map<int, GraphVertex::Ptr> m_Vertices;
	};

	class PointerStructGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override {};
		bool AddEdge(const GraphEdge& edge) override {};
		void PrintTest() override {std::cout << "Test PointerStructGraph" << std::endl;};
	};
}


void AdjListGraph::AddVertex(GraphVertex::Ptr shVertex)
{
	m_Vertices[shVertex->GetId()] = shVertex;
}

bool AdjListGraph::AddEdge(const GraphEdge& edge)
{
	if(m_Vertices.find(edge.m_nSource) == end(m_Vertices) 
	|| m_Vertices.find(edge.m_nDest) == end(m_Vertices) )
	{
		std::cerr << "One of vertices was not found in the graph\n";
		return false;
	}

	m_adjList[edge.m_nSource].push_back(edge.m_nDest);

	return true;
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
