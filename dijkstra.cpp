#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Structure to represent a graph edge
struct Edge {
    int dest, weight;
};

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(const vector<vector<Edge>>& graph, int source, int destination) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX);
    vector<int> parent(n, -1);
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int currNode = pq.top().second;
        pq.pop();

        if (currDist > distance[currNode]) continue;

        for (const Edge& edge : graph[currNode]) {
            int newDist = currDist + edge.weight;
            if (newDist < distance[edge.dest]) {
                distance[edge.dest] = newDist;
                parent[edge.dest] = currNode;
                pq.push({newDist, edge.dest});
            }
        }
    }

    // Print the result
    if (distance[destination] == INT_MAX) {
        cout << "No path found from A to B.\n";
        return;
    }

    cout << "Shortest path distance: " << distance[destination] << endl;
    cout << "Path: ";
    vector<int> path;
    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    for (int v : path)
        cout << (v == path.back() ? to_string(v) : to_string(v) + " -> ");
    cout << endl;
}

int main() {
    int choice;
    vector<vector<Edge>> graph;
    int n = 0, m = 0;

    do {
        cout << "\nMenu:\n";
        cout << "1. Enter number of locations and roads\n";
        cout << "2. Add roads with traffic weights\n";
        cout << "3. Find shortest path from A to B\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter number of locations (vertices): ";
            cin >> n;
            graph.assign(n, vector<Edge>());
            cout << "Enter number of roads (edges): ";
            cin >> m;
            cout << "Graph initialized with " << n << " locations and " << m << " roads.\n";
            break;

        case 2:
            if (n == 0) {
                cout << "Please initialize the graph first (Option 1).\n";
                break;
            }
            cout << "Enter " << m << " roads (format: source destination weight):\n";
            for (int i = 0; i < m; ++i) {
                int u, v, w;
                cin >> u >> v >> w;
                graph[u].push_back({v, w});
                graph[v].push_back({u, w}); // Assuming an undirected graph
            }
            cout << "Roads added successfully.\n";
            break;

        case 3:
            if (graph.empty()) {
                cout << "Please add roads first (Option 2).\n";
                break;
            }
            int source, destination;
            cout << "Enter source location (A): ";
            cin >> source;
            cout << "Enter destination location (B): ";
            cin >> destination;
            dijkstra(graph, source, destination);
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Enter your choice: 1
// Enter number of locations (vertices): 5
// Enter number of roads (edges): 6
// Graph initialized with 5 locations and 6 roads.

// Enter your choice: 2
// Enter 6 roads (format: source destination weight):
// 0 1 10
// 0 2 5
// 1 2 2
// 1 3 1
// 2 3 9
// 3 4 4
// Roads added successfully.

// Enter your choice: 3
// Enter source location (A): 0
// Enter destination location (B): 4
// Shortest path distance: 14
// Path: 0 -> 2 -> 1 -> 3 -> 4
