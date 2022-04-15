#include "gtest/gtest.h"
#include "EdgeList.h"
#include <vector>

class EdgeListTest : public ::testing::Test {
 protected:
    void SetUp() override {
        std::vector<int> vertexList = {1, 2, 3, 4};
        std::vector<std::pair<int, int> > edgeList = {{1, 2},
                                                      {1, 3},
                                                      {2, 4},
                                                      {3, 4}};

        graph = new EdgeList(vertexList, edgeList);
    }
    void TearDown() override {
        delete graph;
    }
    EdgeList* graph;
};

TEST(EdgeListConstructorTest, TestEmptyConstructor) {
    EdgeList* graph = new EdgeList();
    EXPECT_EQ(graph->getNumVertices(), 0);
    delete graph;
}

TEST(EdgeListConstructorTest, TestEmptyMatrixRows) {
    std::vector<int> vertexList = {};
    std::vector<std::pair<int, int>> edgeList = {};
    EXPECT_THROW(new EdgeList(vertexList, edgeList), std::invalid_argument);
}
