#pragma once

#include <optional>
#include <map>
#include <set>
#include <vector>
#include <string>

namespace program::shared::algo
{
    class CDependencyGraph {
    private:
        std::map<std::string, std::set<std::string>> m_graph;
    public:
        void addNode(const std::string& node);
        void addDependency(const std::string& dependent, const std::optional<const std::string>& dependency = std::nullopt);
        std::vector<std::string> topologicalSort() const;
    };
}
