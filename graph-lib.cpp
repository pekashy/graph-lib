#include "graph-lib.h"
#include <iostream>
#include <unordered_map>

namespace
{
	class AdjMatrixGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override {};
		bool AddEdge(const GraphEdge& edge) override {};
		const AdjStorageType& GetAdjacentVertices(int Id) override {return {};};
		GraphVertex::Ptr GetVertex(int Id) const override {	std::cout << "KKKK\n";return nullptr;};
		void PrintTest() override {std::cout << "Test AdjMatrixGraph" << std::endl;};
	};

	class AdjListGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override;
		bool AddEdge(const GraphEdge& edge) override;
		const AdjStorageType& GetAdjacentVertices(int Id) override;
		GraphVertex::Ptr GetVertex(int Id) const override;
		void PrintTest() override {std::cout << "Test AdjListGraph" << std::endl;};
	private:
		std::unordered_map<int, AdjStorageType> m_adjListMap;
		std::unordered_map<int, GraphVertex::Ptr> m_Vertices;

		const AdjStorageType m_EmptyAdjList;
	};

	class PointerStructGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override {};
		bool AddEdge(const GraphEdge& edge) override {};
		const AdjStorageType& GetAdjacentVertices(int Id) override {return {};};
		GraphVertex::Ptr GetVertex(int Id) const override {	std::cout << "CCCCCC\n";return nullptr;};
		void PrintTest() override {std::cout << "Test PointerStructGraph" << std::endl;};
	};
}


void AdjListGraph::AddVertex(GraphVertex::Ptr shVertex)
{
	m_Vertices[shVertex->GetId()] = shVertex;
	m_adjListMap[shVertex->GetId()];
}

bool AdjListGraph::AddEdge(const GraphEdge& edge)
{
	if(m_Vertices.find(edge.m_nSource) == end(m_Vertices) 
	|| m_Vertices.find(edge.m_nDest) == end(m_Vertices) )
	{
		std::cout << "One of vertices was not found in the graph\n";
		return false;
	}
	m_adjListMap[edge.m_nSource].insert(edge.m_nDest);
	m_adjListMap[edge.m_nDest].insert(edge.m_nSource);
	return true;
}

GraphVertex::Ptr AdjListGraph::GetVertex(int Id) const
{
	auto pVertexIt = m_Vertices.find(Id);
	if(pVertexIt == end(m_Vertices))
	{
		std::cout << "Vertex with given ID not present in graph\n";
		return nullptr;
	}
	return pVertexIt->second;
}

const AdjListGraph::AdjStorageType& AdjListGraph::GetAdjacentVertices(int Id)
{
	auto adjListIt = m_adjListMap.find(Id);
	if(adjListIt == end(m_adjListMap))
	{
		std::cout << "Vertex with given ID " << Id << " not present in graph\n";
		return m_EmptyAdjList;
	}
	return adjListIt->second;
}

Graph::Ptr GraphFactory::CreateAdjMatrixGraph()
{
	return std::make_shared<AdjMatrixGraph>();
}

Graph::Ptr GraphFactory::CreateAdjListGraph()
{
	return std::make_shared<AdjListGraph>();
}

Graph::Ptr GraphFactory::CreatePointerStructGraph()
{
	return std::make_shared<PointerStructGraph>();
}
