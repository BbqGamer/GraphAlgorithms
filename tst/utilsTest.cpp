#include "gtest/gtest.h"
#include "utils.h"

TEST(ReadFromFile, Exception) {
    EXPECT_THROW(readGraphFromFile(""), std::runtime_error);
    EXPECT_THROW(readGraphFromFile("Input.txt"), std::runtime_error);
}

TEST(ReadFromFile, GraphFile) {
    Graph g = readGraphFromFile("../tst/data/graph.txt");
    std::vector<int> vertexList = {0, 1, 2, 3};
    std::vector<std::pair<int, int>> edgeList = {{1,2},
                                                 {2,3},
                                                 {1,3}};
    Graph g1 = {vertexList, edgeList};
    EXPECT_EQ(g.vertexList, g1.vertexList);
    EXPECT_EQ(g.edgeList, g1.edgeList);
}
