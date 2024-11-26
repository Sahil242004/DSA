#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// Structure for storing client information
struct Client {
    string name;
    string phone;
};

// Hash Table with Chaining (Separate Chaining with Linked List)
class HashTableChaining {
private:
    vector<list<Client>> table;
    int tableSize;

    int hashFunction(string key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash + ch) % tableSize;
        }
        return hash;
    }

public:
    HashTableChaining(int size) {
        tableSize = size;
        table.resize(tableSize);
    }

    void insert(string name, string phone) {
        int index = hashFunction(name);
        table[index].push_back({name, phone});
    }

    string search(string name) {
        int index = hashFunction(name);
        for (auto &client : table[index]) {
            if (client.name == name) {
                return client.phone;
            }
        }
        return "Not Found";
    }

    int countComparisons(string name) {
        int index = hashFunction(name);
        int comparisons = 0;
        for (auto &client : table[index]) {
            comparisons++;
            if (client.name == name) {
                return comparisons;
            }
        }
        return comparisons;
    }
};

// Hash Table with Open Addressing (Linear Probing)
class HashTableLinearProbing {
private:
    vector<Client> table;
    int tableSize;

    int hashFunction(string key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash + ch) % tableSize;
        }
        return hash;
    }

public:
    HashTableLinearProbing(int size) {
        tableSize = size;
        table.resize(tableSize);
    }

    void insert(string name, string phone) {
        int index = hashFunction(name);
        while (!table[index].name.empty()) {
            index = (index + 1) % tableSize;
        }
        table[index] = {name, phone};
    }

    string search(string name) {
        int index = hashFunction(name);
        while (!table[index].name.empty()) {
            if (table[index].name == name) {
                return table[index].phone;
            }
            index = (index + 1) % tableSize;
        }
        return "Not Found";
    }

    int countComparisons(string name) {
        int index = hashFunction(name);
        int comparisons = 0;
        while (!table[index].name.empty()) {
            comparisons++;
            if (table[index].name == name) {
                return comparisons;
            }
            index = (index + 1) % tableSize;
        }
        return comparisons;
    }
};

// Main function to implement the menu-driven system
int main() {
    int choice, tableSize;

    cout << "Enter table size for Hash Table: ";
    cin >> tableSize;

    HashTableChaining htChaining(tableSize);
    HashTableLinearProbing htLinearProbing(tableSize);

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a new client\n";
        cout << "2. Search for a client's phone number\n";
        cout << "3. Compare search performance between Chaining and Linear Probing\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phone;
                cout << "Enter client's name: ";
                cin >> name;
                cout << "Enter client's phone number: ";
                cin >> phone;

                htChaining.insert(name, phone);
                htLinearProbing.insert(name, phone);
                cout << "Client inserted successfully.\n";
                break;
            }

            case 2: {
                string name;
                cout << "Enter client's name to search: ";
                cin >> name;

                string phoneChaining = htChaining.search(name);
                string phoneLinear = htLinearProbing.search(name);

                cout << "Search Results:\n";
                cout << "Chaining: " << (phoneChaining == "Not Found" ? "Client not found" : phoneChaining) << "\n";
                cout << "Linear Probing: " << (phoneLinear == "Not Found" ? "Client not found" : phoneLinear) << "\n";
                break;
            }

            case 3: {
                string name;
                cout << "Enter client's name to compare search performance: ";
                cin >> name;

                int comparisonsChaining = htChaining.countComparisons(name);
                int comparisonsLinear = htLinearProbing.countComparisons(name);

                cout << "Comparisons for Chaining: " << comparisonsChaining << "\n";
                cout << "Comparisons for Linear Probing: " << comparisonsLinear << "\n";
                break;
            }

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
