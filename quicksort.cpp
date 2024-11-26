// quicksrot
// best case --> O(n log n)
// worst case --> O(n^2)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;


struct Student {
    string name;
    int credits;
};


int partition(vector<Student>& students, int low, int high) {
    int pivot = students[high].credits; 
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (students[j].credits > pivot) { 
            ++i;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}


void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

int main() {

    vector<Student> students = {
        {"Sahil", 85},
        {"Shivam", 92},
        {"Pratiksha", 78},
        {"Tanmay", 95},
        {"Rohan", 88}
    };

    int n = students.size();


    quickSort(students, 0, n - 1);

    cout << "Top 3 Students:\n";
    for (int i = 0; i < min(3, n); ++i) {
        cout << i + 1 << ". " << students[i].name << " - " << students[i].credits << " credits\n";
    }

    return 0;
}
