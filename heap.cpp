/*6. Read the marks obtained by students of second year in an online
examination of particular subject. Find out maximum and minimum marks
obtained in that subject.
Use heap data structure. Analyse the algorithm. */

#include<iostream>
#include<vector>
#include<list>
#include<queue>
using namespace std;



int main() {
    int n;
    cout<<"Enter the number of students\n";
    cin>>n;

    priority_queue<int> maxQueue;
    priority_queue<int, vector<int>, greater<int>> minQueue;
    for(int i =0;i<n; ++i) {
        cout<<"Enter the marks of student "<<i+1<<endl;
        int mark;
        cin>>mark;
        maxQueue.push(mark);
        minQueue.push(mark);
    }

    cout<<"Maximum marks are: "<<maxQueue.top()<<endl;
    cout<<"Minimum marks are: "<<minQueue.top()<<endl;
    return 0;
}



// Enter the number of students
// 5
// Enter the marks of student 1
// 75
// Enter the marks of student 2
// 85
// Enter the marks of student 3
// 60
// Enter the marks of student 4
// 92
// Enter the marks of student 5
// 78
