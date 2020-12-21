#include "lib/graph-lib.h"
#include "objects/common.h"
#include "utils/graph-iterator.h"
#include "utils/dispatcher.h"
#include "utils/visitors.h"

#include "gtest/gtest.h"
#include <iostream>
#include <functional>

TEST(VertexCreationTest, CreateSimpleVertex)
{
	int content = 123;
	auto e = SimpleObjVertex<int>::Create(&content, 0);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(VertexCreationTest, CreateComplexVertex)
{
	auto* o = new FunnyObject();
	auto e = ComplexObjVertex<FunnyObject>::Create(o, 0);
	ASSERT_TRUE(e.get() != nullptr);
}


TEST(EdgeCreationTest, ParamsTest)
{
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	ASSERT_EQ(e.m_nSource, 1);
	ASSERT_EQ(e.m_nDest, 2);
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoSource)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v2);
	ASSERT_FALSE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_NoDest)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	GraphEdge e(v1, v2);
	g->AddVertex(v1);
	ASSERT_FALSE(g->AddEdge(e));
}

TEST(EdgeInsertionTest, InsertSimpleEdgeTest_AdjMatrix_Success)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
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
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
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
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	auto v3 = ComplexObjVertex<FunnyObject>::Create(oF, 3);
	auto v4 = ComplexObjVertex<SadObject>::Create(oS, 4);

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

TEST(GraphTraverseTest, IterateOverFourElements2_AdjList)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	auto v3 = ComplexObjVertex<FunnyObject>::Create(oF, 3);
	auto v4 = ComplexObjVertex<SadObject>::Create(oS, 4);

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

TEST(GraphTraverseTest, IterateOverFourElements2_AdjMatrix)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	auto v3 = ComplexObjVertex<FunnyObject>::Create(oF, 3);
	auto v4 = ComplexObjVertex<SadObject>::Create(oS, 4);

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

// Visitor can be implemented through dispatcher, but I see no point in it for now
TEST(DispatcherTest, TestDispatchTest)
{
	using namespace std::placeholders;
	FunnyObject::Ptr oF = std::make_shared<FunnyObject>();
	SadObject::Ptr oS = std::make_shared<SadObject>();
	std::function<void(Visitor::Ptr)> fF = std::bind(&FunnyObject::Accept, *oF, _1);
	std::function<void(Visitor::Ptr)> fS = std::bind(&SadObject::Accept, *oS, _1);
	VisitorDispatcher<ComplexObject> dispatcher;
	dispatcher.add<FunnyObject>(fF);
	dispatcher.add<SadObject>(fS);

	ComplexObject::Ptr unknown_fF = oF;
	ComplexObject::Ptr unknown_fS = oS;

	auto fF2 = dispatcher.Go(unknown_fF);
	auto fS2 = dispatcher.Go(unknown_fS);
		
	auto cleverVisitor = VisitorFactory::CreateCleverVisitor();
	auto dummyVisitor = VisitorFactory::CreateDummyVisitor();

	fF2(cleverVisitor);
	fS2(dummyVisitor);
}


TEST(VisitorsTest, SmartDummyVisitorsTest_AdjListGraph)
{
	auto g = GraphFactory::CreateAdjListGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	auto v3 = ComplexObjVertex<FunnyObject>::Create(oF, 3);
	auto v4 = ComplexObjVertex<SadObject>::Create(oS, 4);

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

	ASSERT_EQ(v1.get(), v1_recieved.get());
	ASSERT_EQ(v2.get(), v2_recieved.get());
	ASSERT_EQ(v3.get(), v3_recieved.get());
	ASSERT_EQ(v4.get(), v4_recieved.get());
	ASSERT_EQ(graphIt->Next(), nullptr);

	v1_recieved->Accept(cleverVisitor);
	v4_recieved->Accept(cleverVisitor);
	v3_recieved->Accept(cleverVisitor);
	v2_recieved->Accept(cleverVisitor);
}

TEST(VisitorsTest, SmartDummyVisitorsTest_AdjMatrixGraph)
{
	auto g = GraphFactory::CreateAdjMatrixGraph();
	FunnyObject* oF = new FunnyObject();
	SadObject* oS = new SadObject();
	auto v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
	auto v2 = ComplexObjVertex<SadObject>::Create(oS, 2);
	auto v3 = ComplexObjVertex<FunnyObject>::Create(oF, 3);
	auto v4 = ComplexObjVertex<SadObject>::Create(oS, 4);

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

	ASSERT_EQ(v1.get(), v1_recieved.get());
	ASSERT_EQ(v2.get(), v2_recieved.get());
	ASSERT_EQ(v3.get(), v3_recieved.get());
	ASSERT_EQ(v4.get(), v4_recieved.get());
	ASSERT_EQ(graphIt->Next(), nullptr);

	v1_recieved->Accept(cleverVisitor);
	v4_recieved->Accept(cleverVisitor);
	v3_recieved->Accept(cleverVisitor);
	v2_recieved->Accept(cleverVisitor);
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
