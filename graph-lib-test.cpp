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

TEST(EdgeCreationTest, CreateSimpleEdge)
{
	int content = 123;
	auto e = ConcreteGraphEdge<int>::Create(&content, 0, 1);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(EdgeCreationTest, CreateComplexEdge)
{
	auto* o = new FunnyGraphObject();
	auto e = ConcreteGraphEdge<FunnyGraphObject>::Create(o, 0, 0);
	ASSERT_TRUE(e.get() != nullptr);
}

TEST(EdgeCreationTest, ParamsTest)
{
	auto* o = new FunnyGraphObject();
	auto e = ConcreteGraphEdge<FunnyGraphObject>::Create(o, 1, 2);
	ASSERT_TRUE(e->GetSource() == 1);
	ASSERT_TRUE(e->GetDest() == 2);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
