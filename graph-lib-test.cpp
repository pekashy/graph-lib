#include "graph-lib.h"
#include "common.h"
#include "graph-iterator.h"

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
	auto e = ConcreteGraphVertex<int, int>::Create(&content, 0);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(VertexCreationTest, CreateComplexVertex)
{
	auto* o = new FunnyObject();
	auto e = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(o, 0);
	ASSERT_TRUE(e.get() != nullptr);
}


TEST(EdgeCreationTest, ParamsTest)
{
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	ASSERT_EQ(e.m_nSource, 1);
	ASSERT_EQ(e.m_nDest, 2);
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoSource)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v2);
	ASSERT_FALSE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoDest)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	ASSERT_FALSE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_Success)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	g->AddVertex(v2);
	ASSERT_TRUE(g->AddEdge(e));
	ASSERT_EQ(v1.get(), g->GetVertex(1).get());
	ASSERT_EQ(v2.get(), g->GetVertex(2).get());
	auto adj = g->GetAdjacentVertices(1);
	ASSERT_EQ(*adj.begin(), 2);
	auto adj2 = g->GetAdjacentVertices(2);
	ASSERT_EQ(*adj2.begin(), 1);
}


TEST(GraphTraverseTest, IterateOverTwoElements)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	g->AddVertex(v2);
	g->AddEdge(e);

	auto graphIt = GraphIteratorFactory::CreateGraphIterator(g, 1);
	auto v1_recieved = graphIt->Next();
	auto v2_recieved = graphIt->Next();
	ASSERT_EQ(v1.get(), v1_recieved.get());
	ASSERT_EQ(v2.get(), v2_recieved.get());
	ASSERT_EQ(graphIt->Next(), nullptr);

	auto graphIt2 = GraphIteratorFactory::CreateGraphIterator(g, 2);
	auto v2_recieved2 = graphIt2->Next();
	auto v1_recieved2 = graphIt2->Next();
	ASSERT_EQ(v1.get(), v1_recieved2.get());
	ASSERT_EQ(v2.get(), v2_recieved2.get());
	ASSERT_EQ(graphIt2->Next(), nullptr);
}

TEST(GraphTraverseTest, IterateOverFourElements)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	auto v3 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 3);
	auto v4 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 4);

	GraphEdge e12(v1, v2);
	GraphEdge e23(v2, v3);
	GraphEdge e34(v3, v4);

	g->AddVertex(v1);
	g->AddVertex(v2);
	g->AddVertex(v3);
	g->AddVertex(v4);

	g->AddEdge(e12);
	g->AddEdge(e23);
	g->AddEdge(e34);

	auto graphIt = GraphIteratorFactory::CreateGraphIterator(g, 1);
	auto v1_recieved = graphIt->Next();
	auto v2_recieved = graphIt->Next();
	auto v3_recieved = graphIt->Next();
	auto v4_recieved = graphIt->Next();

	ASSERT_EQ(v1.get(), v1_recieved.get());
	ASSERT_EQ(v2.get(), v2_recieved.get());
	ASSERT_EQ(v3.get(), v3_recieved.get());
	ASSERT_EQ(v4.get(), v4_recieved.get());

	ASSERT_EQ(graphIt->Next(), nullptr);
}

TEST(GraphTraverseTest, IterateOverFourElements2)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	auto v3 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 3);
	auto v4 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 4);

	GraphEdge e12(v1, v2);
	GraphEdge e13(v1, v3);
	GraphEdge e14(v1, v4);
	GraphEdge e32(v3, v2);

	g->AddVertex(v1);
	g->AddVertex(v2);
	g->AddVertex(v3);
	g->AddVertex(v4);

	g->AddEdge(e12);
	g->AddEdge(e13);
	g->AddEdge(e14);
	g->AddEdge(e32);

	auto graphIt = GraphIteratorFactory::CreateGraphIterator(g, 1);
	auto v1_recieved = graphIt->Next();
	auto v4_recieved = graphIt->Next();
	auto v3_recieved = graphIt->Next();
	auto v2_recieved = graphIt->Next();

	ASSERT_EQ(v1.get(), v1_recieved.get());
	ASSERT_EQ(v2.get(), v2_recieved.get());
	ASSERT_EQ(v3.get(), v3_recieved.get());
	ASSERT_EQ(v4.get(), v4_recieved.get());

	ASSERT_EQ(graphIt->Next(), nullptr);
}


TEST(VisitorsTest, SmartDummyVisitorsTest)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 1);
	auto v2 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 2);
	auto v3 = ConcreteGraphVertex<FunnyObject, ComplexObject>::Create(oF, 3);
	auto v4 = ConcreteGraphVertex<SadObject, ComplexObject>::Create(oS, 4);

	GraphEdge e12(v1, v2);
	GraphEdge e13(v1, v3);
	GraphEdge e14(v1, v4);
	GraphEdge e32(v3, v2);

	g->AddVertex(v1);
	g->AddVertex(v2);
	g->AddVertex(v3);
	g->AddVertex(v4);

	g->AddEdge(e12);
	g->AddEdge(e13);
	g->AddEdge(e14);
	g->AddEdge(e32);

	auto cleverVisitor = VisitorFactory::CreateCleverVisitor();
	auto graphIt = GraphIteratorFactory::CreateGraphIterator(g, 1);
	auto v1_recieved = graphIt->Next();
	auto v4_recieved = graphIt->Next();
	auto v3_recieved = graphIt->Next();
	auto v2_recieved = graphIt->Next();


	// TODO: Implement Dispatcher for visitor
	cleverVisitor->VisitFunny(v1_recieved);
	cleverVisitor->VisitSad(v1);

}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
