#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    double weight, value, ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

void fractionalKnapsack() {
    int n;
    double capacity;
    std::cout << "Enter the number of items: ";
    std::cin >> n;

    std::vector<Item> items(n);
    std::cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> items[i].weight >> items[i].value;
        items[i].ratio = items[i].value / items[i].weight;
    }

    std::cout << "Enter the knapsack capacity: ";
    std::cin >> capacity;

    std::sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;
    for (auto &item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            maxValue += item.value;
        } else {
            maxValue += item.ratio * capacity;
            break;
        }
    }

    std::cout << "Maximum value in knapsack: " << maxValue << "\n";
}

int main() {
    fractionalKnapsack();
    return 0;
}
