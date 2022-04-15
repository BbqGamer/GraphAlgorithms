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