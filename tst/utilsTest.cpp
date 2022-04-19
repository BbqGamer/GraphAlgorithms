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
