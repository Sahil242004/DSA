#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store student details
struct Student {
    string name;
    int credits;
};

// Merge function to combine two sorted subarrays
void merge(vector<Student>& students, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    vector<Student> leftSub(n1);
    vector<Student> rightSub(n2);

    // Copy data to temporary subarrays
    for (int i = 0; i < n1; ++i)
        leftSub[i] = students[left + i];
    for (int j = 0; j < n2; ++j)
        rightSub[j] = students[mid + 1 + j];

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftSub[i].credits >= rightSub[j].credits) { // Sort in descending order
            students[k] = leftSub[i];
            ++i;
        } else {
            students[k] = rightSub[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of leftSub (if any)
    while (i < n1) {
        students[k] = leftSub[i];
        ++i;
        ++k;
    }

    // Copy remaining elements of rightSub (if any)
    while (j < n2) {
        students[k] = rightSub[j];
        ++j;
        ++k;
    }
}

// Merge Sort function
void mergeSort(vector<Student>& students, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);

        // Merge the sorted halves
        merge(students, left, mid, right);
    }
}

int main() {
    // Example list of students
    vector<Student> students = {
        {"Sahil", 45},
        {"Shivam", 30},
        {"Onkar", 50},
        {"Karan", 40},
        {"Janhvi", 35}
    };

    int n = students.size();

    // Sort the students by credits using Merge Sort
    mergeSort(students, 0, n - 1);

    // Display the sorted students
    cout << "Students sorted by credits (in descending order):\n";
    for (const auto& student : students) {
        cout << student.name << " - " << student.credits << " credits\n";
    }

    return 0;
}
