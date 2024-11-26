#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void primMST(vector<vector<pair<int, int>>>& adj, int V) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    key[0] = 0;
    int mstWeight = 0;

    for (int count = 0; count < V; count++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        inMST[u] = true;
        mstWeight += key[u];

        for (auto& [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << endl;
        }
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

void kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compareEdge);

    UnionFind uf(V);
    vector<Edge> mstEdges;
    int mstWeight = 0;

    for (auto& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mstEdges.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    cout << "Minimum Spanning Tree (Kruskal's Algorithm):\n";
    for (auto& edge : mstEdges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main() {
    int V, E, choice;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pair<int, int>>> adj(V);
    vector<Edge> edges;

    cout << "Enter the edges (u v weight) (0-based index):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        edges.push_back(Edge(u, v, weight));
    }

    do {
        cout << "\nMenu:\n";
        cout << "1. Find MST using Prim's Algorithm\n";
        cout << "2. Find MST using Kruskal's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                primMST(adj, V);
                break;
            case 2:
                kruskalMST(edges, V);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

I/O for 4:

// Enter number of vertices: 4
// Enter number of edges: 5
// Enter the edges (u v weight) (0-based index):
// 0 1 10
// 0 2 6
// 0 3 5
// 1 3 15
// 2 3 4

// Menu:
// 1. Find MST using Prim's Algorithm
// 2. Find MST using Kruskal's Algorithm
// 3. Exit
// Enter your choice: 1 or 2
