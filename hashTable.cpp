#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;

int table_size = 10;

struct Client {
    string name;
    string number;
};

int hashFunction(string name, int table_size) {
    int hash = 0;
    for(char c : name) {
        hash += c;
    }
    return hash % table_size;
}

class HashTableChaining {
    private:
    vector<list<pair<string,string>>> table;

    public:
        HashTableChaining() {
            table.resize(table_size);
        }

        void insert(string name, string phoneNumber) {
            int index = hashFunction(name, table_size);
            table[index].push_back(make_pair(name, phoneNumber));
        }

        string search(string name, int &comparisons) {
            int index = hashFunction(name,table_size);
            for(auto &entry: table[index]) {
                comparisons++;
                cout<<entry.first<<endl;
                cout<<entry.second<<endl;
                if(entry.first == name) {
                    return entry.second;
                }
            }

            return "NOT FOUND!";
        }

        void debugPrint() {
            for (int i = 0; i < table_size; ++i) {
            cout << "Index " << i << ": ";
            for (auto &entry : table[i]) {
                cout << "(" << entry.first << ", " << entry.second << ") ";
            }
            cout << endl;
    }
}

};

class HashTableLinearProbing{
    private:
        vector<pair<string,string>> table;
        vector<bool> isOccupied;
    public:
        HashTableLinearProbing() {
            table.resize(table_size, {"",""});
            isOccupied.resize(table_size,false);
        }

        void insert(string name, string phoneNumber) {
            int index = hashFunction(name, table_size);
            while(isOccupied[index]) {
                index = (index + 1) % table_size;
            }
            table[index] = make_pair(name, phoneNumber);
            isOccupied[index] = true;
        }

        string search(string name, int &comparisson) {
            int index = hashFunction(name, table_size);
            int startIndex = index;
            while(isOccupied[index]) {
                comparisson++;
                if(table[index].first == name) {
                    return table[index].second;
                }
                index = (index + 1) % table_size;
                if(index == startIndex) {
                    break;
                }
            }
            return "NOT FOUND!";
        }

    //     void debugPrint() {
    //         for (int i = 0; i < table_size; ++i) {
    //         cout << "Index " << i << ": ";
    //         for (auto &entry : table[i]) {
    //             cout << "(" << entry.first << ", " << entry.second << ") ";
    //         }
    //         cout << endl;
    // }
};

void compareCollisonTechniques() {
    vector<Client> clients = {{"sahil","932280"},{"om","987564"},{"shivan","534146"},{"vedant","978564"},
    {"pratiksha","564523"},{"janvi","191919"}};

    HashTableChaining htchaining;
    HashTableLinearProbing htlinearprobing;
    for(auto &client: clients) {
        // cout<<"inserting"<<client.name<<" "<<client.number<<endl;
        htchaining.insert(client.name, client.number);
        htlinearprobing.insert(client.name, client.number);
    }
    
    vector<string> searchNames = {"paul","jake","mike","sahil","unknown"};

    for(const auto &name: searchNames) {
        int chainingComparison = 0;
        int probingChaining = 0;

        cout<<"Searching in chaing and probing"<<endl;

        string phoneChaining = htchaining.search(name, chainingComparison);
        string phoneProbing = htlinearprobing.search(name, probingChaining);

        cout<<"Searching for name "<<name<<endl;
        cout<<"seperate chaining phone: "<<phoneChaining<<" ,comparison: "<<chainingComparison<<endl;
        cout<<"linear probing phone: "<<phoneProbing<<" ,comparison: "<<probingChaining<<endl;
        cout<<"----------------------\n";

    }
}

int main() {
    compareCollisonTechniques();
    return 0;

}


