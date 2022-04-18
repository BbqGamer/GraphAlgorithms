#include "gtest/gtest.h"
#include "IncidentMatrix.h"
#include <vector>

class IncidentMatrixTest : public ::testing::Test {
 protected:
    void SetUp() override {
        std::vector<std::vector<int>> incidentMatrix = {{1, 0, 1},
                                                        {1, 1, 0},
                                                        {0, 0, 1},
                                                        {0, 1, 0}};

        graph = new IncidentMatrix(incidentMatrix);
    }
    void TearDown() override {
        delete graph;
    }
    IncidentMatrix* graph;
};

TEST(IncidenctMatrix, InitializeVsConstructor) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 3}};
    Graph g = {vertexList, edgeList};
    IncidentMatrix* graph = new IncidentMatrix(g, 1);
    IncidentMatrix* graph1 = new IncidentMatrix();
    graph1->initialize(g, 1);
    EXPECT_EQ(*graph, *graph1);
    delete graph;
    delete graph1;
}

TEST(IncidentMatrixUndirectedTest, TestAreNeighbors) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {0, 2},
                                                 {1, 0},
                                                 {2, 3}};
    IncidentMatrix* graph = new IncidentMatrix();
    Graph g = {vertexList, edgeList};
    graph->initialize(g, 0);
    EXPECT_EQ(graph->areNeighbors(2,0), true);
    EXPECT_EQ(graph->areNeighbors(3,2), true);
    EXPECT_EQ(graph->areNeighbors(1,3), false);
}

TEST_F(IncidentMatrixTest, TestConstructorVsInitialize) {
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {1, 3},
                                                 {0, 2}};
    IncidentMatrix* graph1 = new IncidentMatrix();
    Graph g = {vertexList, edgeList};
    graph1->initialize(g);
    EXPECT_EQ(*graph, *graph1);
    delete graph1;
}

TEST(IncidentMatrixConstructorTest, TestEmptyConstructor) {
    IncidentMatrix* graph = new IncidentMatrix();
    EXPECT_EQ(graph->getNumVertices(), 0);
    delete graph;
}

TEST(IncidentMatrixConstructorTest, TestEmptyMatrixRows) {
    std::vector<std::vector<int>> incidentMatrix = {};
    EXPECT_THROW(new IncidentMatrix(incidentMatrix), std::invalid_argument);
}

TEST(IncidentMatrixConstructorTest, TestEmptyMatrixColumns) {
    std::vector<std::vector<int>> incidentMatrix = {{},{},{}};
    EXPECT_THROW(new IncidentMatrix(incidentMatrix), std::invalid_argument);
}

TEST(IncidentMatrixConstructorTest, TestNonSquareMatrix) {
    std::vector<std::vector<int>> incidentMatrix = {{1,2},{3,4},{5}};
    EXPECT_THROW(new IncidentMatrix(incidentMatrix), std::invalid_argument);
}

TEST_F(IncidentMatrixTest, IncidentMatrixGetNumVertices) {
    EXPECT_EQ(graph->getNumVertices(), 4);
}

TEST_F(IncidentMatrixTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), true);
    EXPECT_EQ(graph->areNeighbors(0, 3), false);
    EXPECT_EQ(graph->areNeighbors(1, 2), false);
    EXPECT_EQ(graph->areNeighbors(1, 3), true);
}

TEST_F(IncidentMatrixTest, TestAreNeighborsException) {
    EXPECT_THROW(graph->areNeighbors(0, 4), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(45, 6123), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(-1, 1), std::out_of_range);
}