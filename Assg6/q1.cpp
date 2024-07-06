#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjacencyList;

    void dfs(int u, int v, vector<int>& path, vector<vector<int>>& allPaths) {
        path.push_back(u);

        if (u == v) {
            allPaths.push_back(path);
        } else {
            for (int neighbor : adjacencyList[u]) {
                dfs(neighbor, v, path, allPaths);
            }
        }

        path.pop_back();
    }

public:
    void addEdge(int u, int v)
        adjacencyList[u].push_back(v);

    vector<vector<int>> findAllPaths(int u, int v) {
        vector<vector<int>> allPaths;
        vector<int> path;
        dfs(u, v, path, allPaths);
        return allPaths;
    }
};

int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    int u = 0, v = 3;
    vector<vector<int>> paths = g.findAllPaths(u, v);

    cout << "All paths from " << u << " to " << v << ":\n";
    for (const auto& path : paths) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
