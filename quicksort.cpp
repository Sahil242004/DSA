// quicksrot
// best case --> O(n log n)
// worst case --> O(n^2)


#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Partition function for Quick Sort
int partition(vector<pair<string, int>>& arr, int low, int high) {
    int pivot = arr[high].second;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].second >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(vector<pair<string, int>>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to display the top 3 students
void displayTop3(const vector<pair<string, int>>& arr) {
    cout << "\nTop 3 students based on credits:\n";
    for (int i = 0; i < 3 && i < arr.size(); i++) {
        cout << "Student: " << arr[i].first << ", Credits: " << arr[i].second << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<pair<string, int>> students(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter student name: ";
        cin >> students[i].first;
        cout << "Enter credits for " << students[i].first << " over the last 2 years: ";
        cin >> students[i].second;
    }

    // Sort using Quick Sort
    quickSort(students, 0, n - 1);

    // Display top 3 students
    displayTop3(students);

    return 0;
}
    

// Enter the number of students: 5
// Enter student name: Rahul
// Enter credits for Rahul over the last 2 years: 40
// Enter student name: Neha
// Enter credits for Neha over the last 2 years: 50
// Enter student name: Amit
// Enter credits for Amit over the last 2 years: 30
// Enter student name: Simran
// Enter credits for Simran over the last 2 years: 60
// Enter student name: Karan
// Enter credits for Karan over the last 2 years: 45
