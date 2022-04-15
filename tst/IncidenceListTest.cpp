#include "gtest/gtest.h"
#include "IncidenceList.h"
#include <vector>

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
    EXPECT_EQ(graph->areNeighbors(4, 4), false);
}
