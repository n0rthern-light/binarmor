#pragma once

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class CDependencyGraph {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> m_graph;
public:
    void addNode(const std::string& node);
    void addDependency(const std::string& dependent, const std::optional<const std::string>& dependency = std::nullopt);
    std::vector<std::string> topologicalSort() const;
};
