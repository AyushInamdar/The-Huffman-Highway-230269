#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Structure to represent a place with a name and coordinates
struct Place {
    string name;
    int x, y;
    Place(string name, int x, int y) : name(name), x(x), y(y) {}
};

// Structure to represent a node in the A* algorithm
struct Node {
    int index;
    double g_cost;
    double h_cost;
    int parent;

    Node(int idx, double g, double h, int p) : index(idx), g_cost(g), h_cost(h), parent(p) {}

    double f_cost() const { return g_cost + h_cost; }

    bool operator>(const Node& other) const {
        return f_cost() > other.f_cost();
    }
};

// Function to calculate Euclidean distance between two points
double distance(const Place& a, const Place& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// A* algorithm implementation
vector<int> astar(const vector<vector<int>>& graph, const vector<Place>& places, int start, int goal) {
    int n = graph.size();
    vector<double> g_score(n, numeric_limits<double>::infinity());
    vector<int> came_from(n, -1);
    g_score[start] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    open_set.push(Node(start, 0, distance(places[start], places[goal]), -1));

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        if (current.index == goal) {
            vector<int> path;
            for (int at = goal; at != -1; at = came_from[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int neighbor : graph[current.index]) {
            double tentative_g_score = g_score[current.index] + distance(places[current.index], places[neighbor]);

            if (tentative_g_score < g_score[neighbor]) {
                came_from[neighbor] = current.index;
                g_score[neighbor] = tentative_g_score;
                double h_score = distance(places[neighbor], places[goal]);
                open_set.push(Node(neighbor, g_score[neighbor], h_score, current.index));
            }
        }
    }

    return {}; // No path found
}

int main() {
    // List of places with their coordinates
    vector<Place> places = {
        Place("Hall 11", 0, 0),
        Place("Events Ground", 160, 0),
        Place("Pronite Ground", 320, 0),
        Place("New Shopping Complex", 400, 0),
        Place("Health Centre", 700, 0),
        Place("Hall 6", 800, 0),
        Place("Hall 10", 0, 200),
        Place("Hall 9", 0, 380),
        Place("Hall 13", 0, 660),
        Place("Hall 12", 120, 750),
        Place("Hall 8", 160, 80),
        Place("Hall 7", 160, 160),
        Place("Counselling Service", 820, 180),
        Place("Kargil Chowk", 820, 570),
        Place("Hall 2", 400, 570),
        Place("Girls Hostel 1", 570, 320),
        Place("Open Air Theatre", 240, 80),
        Place("Hall 4", 400, 220),
        Place("Hall 3", 400, 320),
        Place("Hall 1", 400, 495),
        Place("Hall 5", 320, 457),
        Place("un1", 0, 560),
        Place("un2", 90, 400),
        Place("un3", 160, 300),
        Place("un4", 160, 160),
        Place("un5", 400, 750),
        Place("un6", 400, 420),
        Place("un7", 400, 80),
        Place("un8", 570, 570),
        Place("un9", 820, 320),
        Place("un10", 820, 0),
    };

    // Map to quickly access place names
    unordered_map<string, int> placeIndex;
    for (int i = 0; i < places.size(); ++i) {
        placeIndex[places[i].name] = i;
    }

    // List of edges (pairs of place names)
    vector<pair<string, string>> edges = {
        {"Hall 11", "Events Ground"},
        {"Events Ground", "Pronite Ground"},
        {"Pronite Ground", "New Shopping Complex"},
        {"New Shopping Complex", "Health Centre"},
        {"Health Centre", "Hall 6"},
        {"Hall 6", "un10"},
        {"Hall 11", "Hall 10"},
        {"Hall 10", "Hall 9"},
        {"Hall 9", "un1"},
        {"un1", "Hall 13"},
        {"Hall 13", "Hall 12"},
        {"Hall 12", "un5"},
        {"un5", "Hall 2"},
        {"Hall 2", "un8"},
        {"un8", "Kargil Chowk"},
        {"Kargil Chowk", "un9"},
        {"un9", "Counselling Service"},
        {"Counselling Service", "un10"},
        {"Hall 10", "un4"},
        {"un4", "Hall 7"},
        {"un4", "Hall 8"},
        {"Hall 8", "Open Air Theatre"},
        {"Hall 8", "Events Ground"},
        {"Open Air Theatre", "un7"},
        {"Hall 2", "Hall 1"},
        {"Hall 1", "un6"},
        {"un6", "Hall 3"},
        {"Hall 3", "Hall 4"},
        {"Hall 4", "un3"},
        {"un3", "Hall 7"},
        {"un3", "un2"},
        {"un1", "un2"},
        {"un2", "Hall 5"},
        {"Hall 5", "Hall 1"},
        {"Hall 5", "un6"},
        {"Hall 4", "un7"},
        {"un7", "New Shopping Complex"},
        {"un8", "Girls Hostel 1"},
        {"Hall 3", "Girls Hostel 1"},
        {"Girls Hostel 1", "Health Centre"}
    };

    // Adjacency list to represent the graph
    vector<vector<int>> adjList(places.size());

    // Build the adjacency list
    for (const auto& edge : edges) {
        int u = placeIndex[edge.first];
        int v = placeIndex[edge.second];
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since the graph is undirected
    }

    // Input start and goal places
    string start_place, goal_place;
    cout << "Enter the starting place: ";
    getline(cin, start_place);
    cout << "Enter the goal place: ";
    getline(cin, goal_place);

    int start = placeIndex[start_place];
    int goal = placeIndex[goal_place];

    // Find the shortest path using A* algorithm
    vector<int> path = astar(adjList, places, start, goal);

    // Output the shortest path and calculate the distance
    if (!path.empty()) {
        cout << "Shortest path from " << start_place << " to " << goal_place << ":" << endl;
        double total_distance = 0;
        for (int i = 0; i < path.size(); ++i) {
            cout << places[path[i]].name;
            if (i < path.size() - 1) {
                double segment_distance = distance(places[path[i]], places[path[i + 1]]);
                total_distance += segment_distance;
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total distance traveled: " << total_distance << " units" << endl;
    } else {
        cout << "No path found between " << start_place << " and " << goal_place << endl;
    }

    return 0;
}
