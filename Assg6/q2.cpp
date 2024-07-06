#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    bool hamPathUtil(vector<int>& path, vector<bool>& visited, int pos) {
        if (pos == V) {
            return true;
        }

        for (int v = 0; v < V; v++) {
            if (isSafe(v, path, pos)) {
                path[pos] = v;
                visited[v] = true;

                if (hamPathUtil(path, visited, pos + 1)) {
                    return true;
                }

                path[pos] = -1;
                visited[v] = false;
            }
        }

        return false;
    }

    bool isSafe(int v, vector<int>& path, int pos) {
        if (!adj[path[pos - 1]][v]) {
            return false;
        }

        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }

        return true;
    }

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    bool hamPath() {
        vector<int> path(V, -1);
        vector<bool> visited(V, false);

        path[0] = 0;
        visited[0] = true;

        if (hamPathUtil(path, visited, 1)) {
            cout << "Hamiltonian Path exists: ";
            for (int v : path) {
                cout << v << " ";
            }
            cout << endl;
            return true;
        }

        cout << "Hamiltonian Path does not exist" << endl;
        return false;
    }

    bool hamCircuit() {
        vector<int> path(V, -1);
        vector<bool> visited(V, false);

        path[0] = 0;
        visited[0] = true;

        if (hamPathUtil(path, visited, 1) && adj[path[V - 1]][path[0]]) {
            cout << "Hamiltonian Circuit exists: ";
            for (int v : path) {
                cout << v << " ";
            }
            cout << path[0] << endl;
            return true;
        }

        cout << "Hamiltonian Circuit does not exist" << endl;
        return false;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.hamPath();
    g.hamCircuit();

    return 0;
}
