#include "gtest/gtest.h"
#include "EdgeList.h"
#include <vector>

class EdgeListTest : public ::testing::Test {
 protected:
    void SetUp() override {
        std::vector<int> vertexList = {1, 2, 3, 4};
        std::vector<std::pair<int, int>> edgeList = {{1, 2},
                                                     {1, 3},
                                                     {2, 4},
                                                     {3, 4}};

        Graph g = {vertexList, edgeList};
        g1 = g;
        graph = new EdgeList(g, 1);
    }
    void TearDown() override {
        delete graph;
    }
    Graph g1;
    EdgeList* graph;
};

TEST_F(EdgeListTest, TestConstructorVsInitialize) {
    std::vector<int> vertexList = {1, 2, 3, 4};
    std::vector<std::pair<int, int>> edgeList = {{1, 2},
                                                 {1, 3},
                                                 {2, 4},
                                                 {3, 4}};

    EdgeList* graph1 = new EdgeList();
    Graph g = {vertexList, edgeList};
    graph1->initialize(g, true);
    EXPECT_EQ(*graph, *graph1);
    delete graph1;
}

TEST(EdgeListConstructorTest, TestEmptyConstructor) {
    EdgeList* graph = new EdgeList();
    EXPECT_EQ(graph->getNumVertices(), 0);
    delete graph;
}

TEST_F(EdgeListTest, IncidentMatrixGetNumVertices) {
    EXPECT_EQ(graph->getNumVertices(), 4);
}

TEST_F(EdgeListTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), false);
    EXPECT_EQ(graph->areNeighbors(1, 3), true);
    EXPECT_EQ(graph->areNeighbors(1, 2), true);
    EXPECT_EQ(graph->areNeighbors(4, 4), false);
}

TEST_F(EdgeListTest, TestDumpGraph) {
    Graph g = graph->dumpGraph();
    EXPECT_EQ(g.vertexList, g1.vertexList);
    EXPECT_EQ(g.edgeList, g1.edgeList);
}