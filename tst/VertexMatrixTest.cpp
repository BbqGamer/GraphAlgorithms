#include "gtest/gtest.h"
#include "VertexMatrix.h"
#include <vector>

class VertexMatrixTest : public ::testing::Test {
 protected:
    void SetUp() override {
        std::vector<std::vector<int>> adjacencyMatrix = {{0, 1, 0},
                                                         {0, 0, 1},
                                                         {1, 1, 0}};
        graph = new VertexMatrix(adjacencyMatrix);
    }
    void TearDown() override {
        delete graph;
    }
    VertexMatrix* graph;
};

TEST_F(VertexMatrixTest, TestConstructorVsInitialize) {
    std::vector<int> vertexList = {0, 1, 2};
    std::vector<std::pair<int, int>> edgeList = {{0, 1},
                                                 {1, 2},
                                                 {2, 0},
                                                 {2, 1}};
    VertexMatrix* graph1 = new VertexMatrix();
    graph1->initialize(vertexList, edgeList, true);
    EXPECT_EQ(*graph, *graph1);
    delete graph1;
}


TEST(VertexMatrixConstructorTest, TestEmptyConstructor) {
    VertexMatrix* graph = new VertexMatrix();
    EXPECT_EQ(graph->getNumVertices(), 0);
    delete graph;
}

TEST(VertexMatrixConstructorTest, TestEmptyMatrixRows) {
    std::vector<std::vector<int>> adjacencyMatrix = {};
    EXPECT_THROW(new VertexMatrix(adjacencyMatrix), std::invalid_argument);
}

TEST(VertexMatrixConstructorTest, TestEmptyMatrixColumns) {
    std::vector<std::vector<int>> adjacencyMatrix = {{},{},{}};
    EXPECT_THROW(new VertexMatrix(adjacencyMatrix), std::invalid_argument);
}

TEST(VertexMatrixConstructorTest, TestNonSquareMatrix) {
    std::vector<std::vector<int>> adjacencyMatrix = {{1,2},{3,4},{5}};
    EXPECT_THROW(new VertexMatrix(adjacencyMatrix), std::invalid_argument);
    std::vector<std::vector<int>> adjacencyMatrix2 = {{1,2},{3,4},{5,6}};
    EXPECT_THROW(new VertexMatrix(adjacencyMatrix), std::invalid_argument);
}

TEST_F(VertexMatrixTest, VertexMatrixGetNumVertices) {
    EXPECT_EQ(graph->getNumVertices(), 3);
}

TEST_F(VertexMatrixTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), true);
    EXPECT_EQ(graph->areNeighbors(1, 0), false);
    EXPECT_EQ(graph->areNeighbors(1, 1), false);
    EXPECT_EQ(graph->areNeighbors(1, 2), true);
}

TEST_F(VertexMatrixTest, TestAreNeighborsException) {
    EXPECT_THROW(graph->areNeighbors(0, 3), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(45, 6123), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(-1, 1), std::out_of_range);
}

// class VertexMatrixInitializeTest : public ::testing::Test {
//  protected:
//     void SetUp() override {
//         std::vector<int> vertexList = {0,1,2};
//         std::vector<std::parit> edgeList = {}
//         std::vector<std::vector<int>> adjacencyMatrix = {{0, 1, 0},
//                                                          {0, 0, 1},
//                                                          {1, 1, 0}};
//         graph = new VertexMatrix(adjacencyMatrix);
//     }
//     void TearDown() override {
//         delete graph;
//     }
//     VertexMatrix* graph;
// };