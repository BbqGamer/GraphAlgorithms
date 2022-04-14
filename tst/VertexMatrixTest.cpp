#include "gtest/gtest.h"
#include "VertexMatrix.h"
#include <vector>

class VertexMatrixTest : public ::testing::Test {
 protected:
    void SetUp() override {
        int a[3][3] = {{0, 1, 0},
                       {1, 0, 1},
                       {0, 1, 0}};
                       
        matrix = new int*[3];

        for (int i = 0; i < 3; i++) {
            matrix[i] = new int[3];
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = a[i][j];
            }
        }

        graph = new VertexMatrix(matrix, 3);
    }

    void TearDown() override {
        delete graph;
    }

    int** matrix;
    VertexMatrix* graph;
};

TEST_F(VertexMatrixTest, TestAreNeighbors) {
    EXPECT_EQ(graph->areNeighbors(0, 1), true);
    EXPECT_EQ(graph->areNeighbors(1, 1), false);
    EXPECT_EQ(graph->areNeighbors(2, 2), false);
}

TEST_F(VertexMatrixTest, TestAreNeighborsException) {
    EXPECT_THROW(graph->areNeighbors(0, 3), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(45, 6123), std::out_of_range);
    EXPECT_THROW(graph->areNeighbors(-1, 1), std::out_of_range);
}