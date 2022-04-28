#include "gtest/gtest.h"
#include "utils.h"

class FileUtilsTest : public ::testing::Test {
 protected:
    void SetUp() override {
        vertexList = {0, 1, 2, 3};
        edgeList =   {{1,2},
                      {2,3},
                      {1,3}};
        g1.vertexList = vertexList;
        g1.edgeList = edgeList;

        g = readGraphFromFile("../tst/data/graph.txt");
    }
    std::vector<int> vertexList;
    std::vector<std::pair<int, int>> edgeList;
    Graph g;
    Graph g1;
};

TEST(ReadFromFile, Exception) {
    EXPECT_THROW(readGraphFromFile(""), std::runtime_error);
    EXPECT_THROW(readGraphFromFile("Input.txt"), std::runtime_error);
}

TEST_F(FileUtilsTest, ReadGraphFile) {
    EXPECT_EQ(g.vertexList, g1.vertexList);
    EXPECT_EQ(g.edgeList, g1.edgeList);
}

TEST_F(FileUtilsTest, WriteGraphFile) {
    writeGraphToFile("../tst/data/a.txt", g);
    g = readGraphFromFile("../tst/data/graph.txt");
    EXPECT_EQ(g.vertexList, g1.vertexList);
    EXPECT_EQ(g.edgeList, g1.edgeList);
}

TEST_F(FileUtilsTest, CyclicGraph) {
    std::vector<bool> visited = std::vector<bool>(4, false);
    EXPECT_EQ(hasCycle(g1.edgeList, 2, visited, g1.edgeList[2].first), 0);
    visited = std::vector<bool>(4, false);
    EXPECT_EQ(hasCycle(g.edgeList, 2, visited, g.edgeList[2].first), 0);
}

class CyclicTest : public ::testing::Test {
 protected:
    void SetUp() override {
        edges =     {{0,1},
                    {1,2},
                    {2,3},
                    {3,0}};

        visited = std::vector<bool>(4, false);
    }
    std::vector<std::pair<int, int>> edges;
    std::vector<bool> visited;
};

TEST_F(CyclicTest, IsCyclic) {
    EXPECT_EQ(hasCycle(edges, 3, visited, edges[3].first), 1);
}

TEST(CycleTest, SingleEdge) {
    std::vector<bool> visited = std::vector<bool>(4, false);
    std::vector<std::pair<int, int>> edges = {{0,1}};
    EXPECT_EQ(hasCycle(edges, 0, visited, edges[0].first), 0);
}

TEST(CycleTest, TwoEdgesWithCycle) {
    std::vector<bool> visited = std::vector<bool>(4, false);
    std::vector<std::pair<int, int>> edges = {{0,1},
                                              {1,0}};
    EXPECT_EQ(hasCycle(edges, 1, visited, edges[1].first), 1);
}

TEST(CycleTest, TwoEdgesNoCycle) {
    std::vector<bool> visited = std::vector<bool>(4, false);
    std::vector<std::pair<int, int>> edges = {{0,1},
                                              {2,0}};
    EXPECT_EQ(hasCycle(edges, 1, visited, edges[1].first), 0);
}