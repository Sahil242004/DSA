#include <iostream>
#include <vector>
#include <climits>
using namespace std;

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
            cout << parent[i] << " - " << i << " : " << key[i] << endl;
        }
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter the edges (u v weight) (0-based index):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    primMST(adj, V);

    return 0;
}

// Enter number of vertices: 4
// Enter number of edges: 5
// Enter the edges (u v weight) (0-based index):
// 0 1 10
// 0 2 6
// 0 3 5
// 1 3 15
// 2 3 4
