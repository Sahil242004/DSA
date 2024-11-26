#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
#include <string>
using namespace std;


struct Edge {
    string destination;
    int cost; // Can represent time or fuel cost
    Edge(string dest, int c) : destination(dest), cost(c) {}
};


class FlightNetwork {
private:
    
    unordered_map<string, list<Edge>> adjList;

public:
   
    void addCity(string city) {
        
        if (adjList.find(city) == adjList.end()) {
            adjList[city] = list<Edge>();
        }
    }

    
    void addFlight(string cityA, string cityB, int cost) {
        adjList[cityA].push_back(Edge(cityB, cost));
        adjList[cityB].push_back(Edge(cityA, cost));
    }


    bool isConnected() {
        if (adjList.empty()) return true;

        unordered_map<string, bool> visited;
        string startCity = adjList.begin()->first;
        queue<string> q;

        
        q.push(startCity);
        visited[startCity] = true;
        int visitedCount = 0;

        while (!q.empty()) {
            string city = q.front();
            q.pop();
            visitedCount++;

            for (const Edge& edge : adjList[city]) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    q.push(edge.destination);
                }
            }
        }

        
        return visitedCount == adjList.size();
    }

    
    void printNetwork() {
        for (const auto& pair : adjList) {
            string city = pair.first;
            cout << city << " -> ";
            for (const Edge& edge : pair.second) {
                cout << "(" << edge.destination << ", " << edge.cost << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    FlightNetwork network;

    
    network.addCity("Pune");
    network.addCity("Mumbai");
    network.addCity("Banlore");
    network.addCity("Jammu");
    network.addCity("Andaman");

    
    network.addFlight("Pune", "Banglore", 300); 
    network.addFlight("Pune", "Andaman", 120);
    network.addFlight("Jaammu", "Mumbai", 200);
    network.addFlight("Mumbai", "Banglore", 180);
    network.addFlight("Banglore", "Andaman", 150);

    
    cout << "Flight Network (Adjacency List Representation):" << endl;
    network.printNetwork();

    
    if (network.isConnected()) {
        cout << "\nThe flight network is connected." << endl;
    } else {
        cout << "\nThe flight network is NOT connected." << endl;
    }

    return 0;
}
