#include <iostream>
using namespace std;

#define SIZE 5

struct Node {
    int data;
    int priority;
};

class PriorityQueue {
    Node queue[SIZE];
    int count;

public:
    PriorityQueue() {
        count = 0;
    }

    void enqueue(int value, int priority) {
        if (count == SIZE) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        queue[count].data = value;
        queue[count].priority = priority;
        count++;
        cout << "Inserted: " << value << " with priority " << priority << endl;
    }

    void dequeue() {
        if (count == 0) {
            cout << "Queue Underflow!" << endl;
            return;
        }
        int highestPriorityIndex = 0;
        for (int i = 1; i < count; i++) {
            if (queue[i].priority < queue[highestPriorityIndex].priority) {
                highestPriorityIndex = i;
            }
        }
        cout << "Deleted: " << queue[highestPriorityIndex].data << endl;
        for (int i = highestPriorityIndex; i < count - 1; i++) {
            queue[i] = queue[i + 1];
        }
        count--;
    }

    void display() {
        if (count == 0) {
            cout << "Queue is Empty!" << endl;
            return;
        }
        cout << "Priority Queue: ";
        for (int i = 0; i < count; i++) {
            cout << "(" << queue[i].data << ", P=" << queue[i].priority << ") ";
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;
    pq.enqueue(10, 2);
    pq.enqueue(20, 1);
    pq.enqueue(30, 3);
    pq.display();
    pq.dequeue();
    pq.display();
    return 0;
}
