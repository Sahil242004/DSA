#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Merge function to merge two halves
void merge(vector<pair<string, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<string, int>> leftArr(n1);
    vector<pair<string, int>> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].second <= rightArr[j].second) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<pair<string, int>>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Function to display the student credits
void displayCredits(const vector<pair<string, int>>& arr) {
    for (const auto& student : arr) {
        cout << "Student: " << student.first << ", Credits: " << student.second << endl;
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
        cout << "Enter credits for " << students[i].first << ": ";
        cin >> students[i].second;
    }

    // Sort using Merge Sort
    mergeSort(students, 0, n - 1);

    cout << "\nSorted student credits:\n";
    displayCredits(students);

    return 0;
}
