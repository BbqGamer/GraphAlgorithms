#include "gtest/gtest.h"
#include "IncidenceList.h"
#include <vector>
#include "utils.h"

class IncidenceListTest : public ::testing::Test {
 protected:
    void SetUp() override {
        std::vector<std::vector<int>> incidenceList = {{1, 2},
                                                       {0},
                                                       {0, 3},
                                                       {2}};

        graph = new IncidenceList(incidenceList);
    }
    void TearDown() override {
        delete graph;
    }
    IncidenceList* graph;
};

TEST_F(IncidenceListTest, TestConstructorVsInitialize) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 0},
                                                 {2, 3},
                                                 {3, 2}};
    IncidenceList* graph1 = new IncidenceList();
    Graph g = {vertexList, edgeList};
    graph1->initialize(g, true);
    EXPECT_EQ(*graph, *graph1);
    delete graph1;
}

TEST_F(IncidenceListTest, TestDumpGraph) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 3}};
    Graph g = {vertexList, edgeList};
    Graph g1 = graph->dumpGraph();
    EXPECT_EQ(g.vertexList, g1.vertexList);
    EXPECT_EQ(g.edgeList, g1.edgeList);
}

TEST(IncidenceList, InitializeVsConstructor) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 3}};
    Graph g = {vertexList, edgeList};
    IncidenceList* graph = new IncidenceList(g, 1);
    IncidenceList* graph1 = new IncidenceList();
    graph1->initialize(g, 1);
    EXPECT_EQ(*graph, *graph1);
    delete graph;
    delete graph1;
}

TEST(IncidenceListUndirectedTest, TestAreNeighbors) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 3}};
    IncidenceList* graph = new IncidenceList();
    Graph g = {vertexList, edgeList};
    graph->initialize(g, 0);
    EXPECT_EQ(graph->areNeighbors(2,0), true);
    EXPECT_EQ(graph->areNeighbors(3,2), true);
    EXPECT_EQ(graph->areNeighbors(1,3), false);
}

TEST(IncidenceListConstructorTest, TestEmptyConstructor) {
    IncidenceList* graph = new IncidenceList();
    EXPECT_EQ(graph->getNumVertices(), 0);
    delete graph;
}

TEST_F(IncidenceListTest, IncidentMatrixGetNumVertices) {
    EXPECT_EQ(graph->getNumVertices(), 4);
}

TEST_F(IncidenceListTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), true);
    EXPECT_EQ(graph->areNeighbors(1, 3), false);
    EXPECT_EQ(graph->areNeighbors(2, 3), true);
    EXPECT_EQ(graph->areNeighbors(3, 3), false);
}

TEST_F(IncidenceListTest, TestAreNeighborsExpception) {
    EXPECT_THROW(graph->areNeighbors(0, 4), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(-420, 69), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(2137, 666), std::out_of_range);
}

TEST(TopologicalSort, TestTopologicalSort) {
    IncidenceList graph = IncidenceList(readGraphFromFile("../tst/data/DAG-5.tst"), 1);
    std::vector<int> expected = {5,4,2,3,1,0};
    EXPECT_EQ(expected, graph.topologicalSort());
}