#include "graph-lib.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>

namespace
{
	struct HashIndex
	{
		size_t operator() (const std::pair<int, int>& pr) const
		{
			static std::hash<int> z;
			return z(pr.first) + z(pr.second);
		}
	};

	class AdjMatrixGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override;
		bool AddEdge(const GraphEdge& edge) override;
		const AdjStorageType& GetAdjacentVertices(int Id) override;
		GraphVertex::Ptr GetVertex(int Id) const override;
	private:
		std::unordered_map<std::pair<int, int>, int, HashIndex> m_adjacencyMatrix;
		std::unordered_map<int, GraphVertex::Ptr> m_vertices;
		std::unordered_map<int, AdjStorageType> m_adjListMap;

		std::set<int> m_ids;
		AdjStorageType m_ReturnAdjList;
	};

	class AdjListGraph : public Graph
	{
	public:
		void AddVertex(GraphVertex::Ptr shVertex) override;
		bool AddEdge(const GraphEdge& edge) override;
		const AdjStorageType& GetAdjacentVertices(int Id) override;
		GraphVertex::Ptr GetVertex(int Id) const override;
	private:
		std::unordered_map<int, AdjStorageType> m_adjListMap;
		std::unordered_map<int, GraphVertex::Ptr> m_vertices;

		const AdjStorageType m_EmptyAdjList;
	};
}

void AdjMatrixGraph::AddVertex(GraphVertex::Ptr shVertex)
{
	auto id = shVertex->GetId();
	m_vertices[id] = shVertex;
	m_ids.insert(id);
}

bool AdjMatrixGraph::AddEdge(const GraphEdge& edge)
{
	if(m_vertices.find(edge.m_nSource) == end(m_vertices) 
	|| m_vertices.find(edge.m_nDest) == end(m_vertices) )
	{
		std::cout << "One of vertices was not found in the graph\n";
		return false;
	}
	m_adjacencyMatrix[std::minmax(edge.m_nSource, edge.m_nDest)] = 1;
	return true;
}

GraphVertex::Ptr AdjMatrixGraph::GetVertex(int Id) const
{
	auto pVertexIt = m_vertices.find(Id);
	if(pVertexIt == end(m_vertices))
	{
		std::cout << "Vertex with given ID not present in graph\n";
		return nullptr;
	}
	return pVertexIt->second;
}

const Graph::AdjStorageType& AdjMatrixGraph::GetAdjacentVertices(int Id)
{
	m_ReturnAdjList.clear();
	for(int second_id : m_ids)
	{
		auto index = std::minmax(second_id, Id);
		auto vertexIdIt = m_adjacencyMatrix.find(index);
		if(vertexIdIt != end(m_adjacencyMatrix))
		{
			m_ReturnAdjList.insert(second_id);
		}
	}
	return m_ReturnAdjList;
}


void AdjListGraph::AddVertex(GraphVertex::Ptr shVertex)
{
	m_vertices[shVertex->GetId()] = shVertex;
	m_adjListMap[shVertex->GetId()];
}

bool AdjListGraph::AddEdge(const GraphEdge& edge)
{
	if(m_vertices.find(edge.m_nSource) == end(m_vertices) 
	|| m_vertices.find(edge.m_nDest) == end(m_vertices) )
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
	auto pVertexIt = m_vertices.find(Id);
	if(pVertexIt == end(m_vertices))
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

// See no point in pointer struct graph for this task
Graph::Ptr GraphFactory::CreatePointerStructGraph()
{
	return std::make_shared<AdjListGraph>();
}
