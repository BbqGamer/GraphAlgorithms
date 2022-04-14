#include "gtest/gtest.h"
#include "VertexMatrix.h"
#include <vector>

class IncidentMatrixTest : public ::testing::Test {
 protected:
    void SetUp() override {
        int a[4][3] = {{0,1},
                       {1,2},
                       {2,0},
                       {2,1}};


        for (int i = 0; i < 4; i++) {
            matrix[i] = new int[2];
            for (int j = 0; j < 2; j++) {
                matrix[i][j] = a[i][j];
            }
        }

        graph = new IncidentMatrix(matrix, 3, 4);
    }

    void TearDown() override {
        delete graph;
    }

    int** matrix;
    VertexMatrix* graph;
};

TEST_F(IncidentMatrixTest, VertexMatrixGetNumVertices) {
    EXPECT_EQ(graph->getNumVertices(), 3);
}

TEST_F(IncidentMatrixTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), true);
    EXPECT_EQ(graph->areNeighbors(1, 1), false);
    EXPECT_EQ(graph->areNeighbors(2, 2), false);
}

TEST_F(IncidentMatrixTest, TestAreNeighborsException) {
    EXPECT_THROW(graph->areNeighbors(0, 3), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(45, 6123), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(-1, 1), std::out_of_range);
}