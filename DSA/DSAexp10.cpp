#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    
    vector<int> marks(n);
    cout << "Enter the marks obtained by students: ";
    for(int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(int mark : marks) {
        maxHeap.push(mark);
        minHeap.push(mark);
    }

    int maxMarks = maxHeap.top();
    int minMarks = minHeap.top();

    cout << "Maximum marks obtained: " << maxMarks << endl;
    cout << "Minimum marks obtained: " << minMarks << endl;

    return 0;
}