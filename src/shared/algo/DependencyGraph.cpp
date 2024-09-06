#include "DependencyGraph.hpp"
#include "../RuntimeException.hpp"
#include <queue>

void CDependencyGraph::addNode(const std::string& node) {
    if (m_graph.find(node) == m_graph.end()) {
        m_graph[node] = {};
    }
}

void CDependencyGraph::addDependency(const std::string& dependent, const std::optional<const std::string>& dependency) {
    addNode(dependent);
    if (dependency.has_value()) {
        addNode(dependency.value());
        m_graph[dependency.value()].insert(dependent);
    }
}

std::vector<std::string> CDependencyGraph::topologicalSort() const {
    std::vector<std::string> sorted;
    std::queue<std::string> q;

    std::map<std::string, int> localInDegree = { };

    for (const auto& [node, dependencies] : m_graph) {
        if (localInDegree.find(node) == localInDegree.end()) {
            localInDegree[node] = 0;
        }
    }
    for (const auto& [node, dependencies] : m_graph) {
        for (const auto& dependency : dependencies) {
            ++localInDegree[dependency];
        }
    }

    for (const auto& [node, degree] : localInDegree) {
        if (degree == 0) {
            q.push(node);
        }
    }

    while (q.empty() == false) {
        const auto& node = q.front();
        q.pop();
        sorted.push_back(node);

        for (const auto& neighbor : m_graph.at(node)) {
            if (--localInDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (sorted.size() == m_graph.size()) {
        return sorted;
    } else {
        throw RuntimeException("Dependency graph cycle detected!");
    }
}
