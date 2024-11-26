#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adjList;  // Adjacency List with time/cost

public:
    void addCity(string city) {
        if (adjList.find(city) == adjList.end()) {
            adjList[city] = vector<pair<string, int>>();
        } else {
            cout << "City already exists!" << endl;
        }
    }

    void addFlight(string city1, string city2, int cost) {
        adjList[city1].push_back(make_pair(city2, cost));
        adjList[city2].push_back(make_pair(city1, cost));
    }

    void isConnected() {
        if (adjList.empty()) {
            cout << "No cities in the graph!" << endl;
            return;
        }

        unordered_map<string, bool> visited;
        int component_count = 0;

        for (auto& city : adjList) {
            if (!visited[city.first]) {
                component_count++;
                BFS(city.first, visited);
            }
        }

        if (component_count == 1) {
            cout << "The graph is connected." << endl;
        } else {
            cout << "The graph is not connected. Number of components: " << component_count << endl;
        }
    }

private:
    void BFS(string start, unordered_map<string, bool>& visited) {
        queue<string> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string city = q.front();
            q.pop();

            for (auto& neighbor : adjList[city]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "1. Add City\n";
        cout << "2. Add Flight Path\n";
        cout << "3. Check if Graph is Connected\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string city;
                cout << "Enter city name: ";
                cin >> city;
                g.addCity(city);
                cout << "City added!" << endl;
                break;
            }
            case 2: {
                string city1, city2;
                int cost;
                cout << "Enter first city: ";
                cin >> city1;
                cout << "Enter second city: ";
                cin >> city2;
                cout << "Enter cost (time or fuel): ";
                cin >> cost;
                g.addFlight(city1, city2, cost);
                break;
            }
            case 3:
                g.isConnected();
                break;
            case 4:
                cout << "Exiting...Thank You! Have a nice day!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}

// Enter your choice: 1
// Enter city name: Mumbai
// City added!

// Enter your choice: 1
// Enter city name: Delhi
// City added!

// Enter your choice: 2
// Enter first city: Mumbai
// Enter second city: Delhi
// Enter cost (time or fuel): 300
// City added!

// Enter your choice: 3
// The graph is connected.

// Enter your choice: 4
// Exiting...Thank You! Have a nice day!
