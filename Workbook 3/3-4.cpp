#include <bits/stdc++.h>
using namespace std;

int minCostToConnectRopes(vector<int>& ropes) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // creating min heap with external library

    for (int rope : ropes) {
        minHeap.push(rope);
    }

    int totalCost = 0;

    while (minHeap.size() > 1) {
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        int cost = first + second;
        totalCost += cost;

        minHeap.push(cost);

        cout << "Connect ropes with length " << first << " and " << second 
             << ". Costs: " << cost << ". Total costs: " << totalCost << endl;
    }

    return totalCost;
}

int main() {
    vector<int> ropes = {4, 3, 2, 6};

    cout << "Initial length of ropes: ";
    for (int rope : ropes) {
        cout << rope << " ";
    }
    cout << endl;

    int totalCost = minCostToConnectRopes(ropes);

    cout << "\nMinimum cost to connect all ropes: " << totalCost << endl;

    return 0;
}