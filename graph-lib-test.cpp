#include "graph-lib.h"
#include "common.h"
#include "gtest/gtest.h"

#include <iostream>

TEST(GraphCreationTest, CreateAdjMatrixGraph)
{
	auto g = GraphFactory::CreateAdjMatrixGraph();
	g->PrintTest();
	ASSERT_TRUE(g.get() != nullptr);
}

TEST(GraphCreationTest, CreatePointerStructGraph)
{
	auto g = GraphFactory::CreatePointerStructGraph();
	g->PrintTest();
	ASSERT_TRUE(g.get() != nullptr);
}

TEST(GraphCreationTest, CreateAdjListGraph)
{
	auto g = GraphFactory::CreateAdjListGraph();
	g->PrintTest();
	ASSERT_TRUE(g.get() != nullptr);
}

TEST(VertexCreationTest, CreateSimpleVertex)
{
	int content = 123;
	auto e = ConcreteGraphVertex<int>::Create(&content, 0);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(VertexCreationTest, CreateComplexVertex)
{
	auto* o = new FunnyObject();
	auto e = ConcreteGraphVertex<FunnyObject>::Create(o, 0);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(EdgeCreationTest, ParamsTest)
{
	auto* o = new FunnyObject();
	auto v1 = ConcreteGraphVertex<FunnyObject>::Create(o, 1);
	auto v2 = ConcreteGraphVertex<FunnyObject>::Create(o, 2);
	GraphEdge e(v1, v2);
	ASSERT_TRUE(e.m_nSource== 1);
	ASSERT_TRUE(e.m_nDest == 2);
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_Success)
{
	auto g = GraphFactory::CreateAdjMatrixGraph();
	auto* o = new FunnyObject();
	auto v1 = ConcreteGraphVertex<FunnyObject>::Create(o, 1);
	auto v2 = ConcreteGraphVertex<FunnyObject>::Create(o, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	g->AddVertex(v2);
	ASSERT_TRUE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoSource)
{
	auto g = GraphFactory::CreateAdjMatrixGraph();
	auto* o = new FunnyObject();
	auto v1 = ConcreteGraphVertex<FunnyObject>::Create(o, 1);
	auto v2 = ConcreteGraphVertex<FunnyObject>::Create(o, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v2);
	ASSERT_FALSE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoDest)
{
	auto g = GraphFactory::CreateAdjMatrixGraph();
	auto* o = new FunnyObject();
	auto v1 = ConcreteGraphVertex<FunnyObject>::Create(o, 1);
	auto v2 = ConcreteGraphVertex<FunnyObject>::Create(o, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	ASSERT_FALSE(g->AddEdge(e));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
