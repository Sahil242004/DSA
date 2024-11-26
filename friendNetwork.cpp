

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <ctime>
#include<climits>


struct User {
    int id;
    std::string name;
    int dayOfBirth;
    int monthOfBirth;
    int numComments;
    std::vector<int> friends; 

    User()
        : id(0), name(""), dayOfBirth(0), monthOfBirth(0), numComments(0) {}

    User(int id, const std::string& name, int day, int month, int comments)
        : id(id), name(name), dayOfBirth(day), monthOfBirth(month),
          numComments(comments) {}
};

// Graph structure for friend network
class FriendNetwork {
private:
    std::unordered_map<int, User> users; // Map of userID to User object

public:
    // Add a new user
    void addUser(int id, const std::string& name, int day, int month, int comments) {
        users[id] = User(id, name, day, month, comments);
    }

    // Add a friendship (bidirectional)
    void addFriendship(int user1, int user2) {
        users[user1].friends.push_back(user2);
        users[user2].friends.push_back(user1);
    }

    // Find the user with the maximum number of friends
    void findMaxFriends() {
        int maxFriends = 0;
        int userWithMaxFriends = -1;

        for (const auto& pair : users) {
            const User& user = pair.second;
            if (user.friends.size() > maxFriends) {
                maxFriends = user.friends.size();
                userWithMaxFriends = user.id;
            }
        }

        std::cout << "User with maximum friends: " << users[userWithMaxFriends].name
                  << " with " << maxFriends << " friends.\n";
    }

    // Find the user with maximum and minimum comments
    void findMaxMinComments() {
        int maxComments = INT_MIN, minComments = INT_MAX;
        int userWithMaxComments = -1, userWithMinComments = -1;

        for (const auto& pair : users) {
            const User& user = pair.second;
            if (user.numComments > maxComments) {
                maxComments = user.numComments;
                userWithMaxComments = user.id;
            }
            if (user.numComments < minComments) {
                minComments = user.numComments;
                userWithMinComments = user.id;
            }
        }

        std::cout << "User with maximum comments: " << users[userWithMaxComments].name
                  << " with " << maxComments << " comments.\n";
        std::cout << "User with minimum comments: " << users[userWithMinComments].name
                  << " with " << minComments << " comments.\n";
    }

    // Find users having a birthday in the current month
    void findBirthdayInMonth(int currentMonth) {
        std::cout << "Users having birthday in month " << currentMonth << ":\n";
        for (const auto& pair : users) {
            const User& user = pair.second;
            if (user.monthOfBirth == currentMonth) {
                std::cout << user.name << " has a birthday on " << user.dayOfBirth
                          << ".\n";
            }
        }
    }

    // Perform DFS traversal
    void DFS(int startUserId) {
        std::unordered_map<int, bool> visited;
        std::cout << "DFS Traversal starting from " << users[startUserId].name << ": ";
        DFSUtil(startUserId, visited);
        std::cout << std::endl;
    }

    // Utility function for DFS
    void DFSUtil(int userId, std::unordered_map<int, bool>& visited) {
        visited[userId] = true;
        std::cout << users[userId].name << " ";

        for (int friendId : users[userId].friends) {
            if (!visited[friendId]) {
                DFSUtil(friendId, visited);
            }
        }
    }

    // Perform BFS traversal
    void BFS(int startUserId) {
        std::unordered_map<int, bool> visited;
        std::queue<int> q;
        visited[startUserId] = true;
        q.push(startUserId);

        std::cout << "BFS Traversal starting from " << users[startUserId].name << ": ";

        while (!q.empty()) {
            int userId = q.front();
            q.pop();
            std::cout << users[userId].name << " ";

            for (int friendId : users[userId].friends) {
                if (!visited[friendId]) {
                    visited[friendId] = true;
                    q.push(friendId);
                }
            }
        }
        std::cout << std::endl;
    }
};

// Main function
int main() {
    FriendNetwork network;

    // Add some users
    network.addUser(1, "Sahil", 24, 8, 100);
    network.addUser(2, "Shekhar", 18, 3, 105);
    network.addUser(3, "Pradnya", 02, 1, 110);

    // Add friendships
    network.addFriendship(1, 2);
    network.addFriendship(1, 3);
    network.addFriendship(2, 3);
    network.addFriendship(3, 2);

    // 1. Find who has the maximum number of friends
    network.findMaxFriends();

    // 2. Find who has posted the maximum and minimum comments
    network.findMaxMinComments();

    // 3. Find users who have birthdays in the current month (October)
    network.findBirthdayInMonth(10);

    // Perform DFS traversal
    network.DFS(1);

    // Perform BFS traversal
    network.BFS(1);

    return 0;
}
