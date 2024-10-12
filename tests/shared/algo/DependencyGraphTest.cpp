#include <shared/algo/DependencyGraph.hpp>
#include <shared/RuntimeException.hpp>
#include <gtest/gtest.h>

TEST(CDependencyGraphTest, SimpleGraph) {
    CDependencyGraph graph;
    graph.addDependency("A", "B");
    graph.addDependency("B", "C");

    std::vector<std::string> sorted = graph.topologicalSort();
    ASSERT_EQ(sorted.size(), 3);
    EXPECT_EQ(sorted[0], "C");
    EXPECT_EQ(sorted[1], "B");
    EXPECT_EQ(sorted[2], "A");
}

TEST(CDependencyGraphTest, DisconnectedGraph) {
    CDependencyGraph graph;
    graph.addDependency("A", "B");
    graph.addDependency("C", "D");

    std::vector<std::string> sorted = graph.topologicalSort();
    ASSERT_EQ(sorted.size(), 4);
    ASSERT_TRUE(
        sorted == (std::vector<std::string> { "D", "B", "C", "A" }) ||
        sorted == (std::vector<std::string> { "B", "D", "C", "A" }) ||
        sorted == (std::vector<std::string> { "D", "B", "A", "C" }) ||
        sorted == (std::vector<std::string> { "B", "D", "A", "C" })
    );
}

TEST(CDependencyGraphTest, CycleDetection) {
    CDependencyGraph graph;
    graph.addDependency("A", "B");
    graph.addDependency("B", "C");
    graph.addDependency("C", "A");

    EXPECT_THROW(graph.topologicalSort(), RuntimeException);
}

TEST(CDependencyGraphTest, NoDependencies) {
    CDependencyGraph graph;
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");

    std::vector<std::string> sorted = graph.topologicalSort();
    ASSERT_EQ(sorted.size(), 3);
    EXPECT_TRUE((sorted[0] == "A" && sorted[1] == "B" && sorted[2] == "C") ||
                (sorted[0] == "B" && sorted[1] == "A" && sorted[2] == "C") ||
                (sorted[0] == "C" && sorted[1] == "A" && sorted[2] == "B"));
}

TEST(CDependencyGraphTest, ComplexDependencies) {
    CDependencyGraph graph;

    graph.addDependency("A", "B");    // A -> B
    graph.addDependency("A", "C");    // A -> C
    graph.addDependency("B", "D");    // B -> D
    graph.addDependency("C", "D");    // C -> D
    graph.addDependency("D", "E");    // D -> E
    graph.addDependency("H");    
    graph.addDependency("I");   
    graph.addDependency("F", "E");    // F -> E
    graph.addDependency("G", "E");    // G -> E
    graph.addNode("J"); 

    auto sorted = graph.topologicalSort();
    EXPECT_EQ(sorted.size(), 10);

    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "A") > std::find(sorted.begin(), sorted.end(), "B"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "A") > std::find(sorted.begin(), sorted.end(), "E"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "A") > std::find(sorted.begin(), sorted.end(), "C"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "B") > std::find(sorted.begin(), sorted.end(), "D"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "C") > std::find(sorted.begin(), sorted.end(), "D"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "D") > std::find(sorted.begin(), sorted.end(), "E"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "F") > std::find(sorted.begin(), sorted.end(), "E"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "G") > std::find(sorted.begin(), sorted.end(), "E"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "H") < std::find(sorted.begin(), sorted.end(), "G"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "I") < std::find(sorted.begin(), sorted.end(), "D"));
    EXPECT_TRUE(std::find(sorted.begin(), sorted.end(), "J") < std::find(sorted.begin(), sorted.end(), "A"));
}
