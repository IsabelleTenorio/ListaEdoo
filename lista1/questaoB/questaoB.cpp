#include <iostream>
using namespace std;

template <typename T>
class Node {
    public:
        T data;
        Node<T>* next;
        Node(T data) : data(data), next(nullptr) {};
};

template <typename T>
class Queue {
    private:
        Node<T>* front;
        Node<T>* rear;
        int size;

    public:
        Queue() : front(nullptr), rear(nullptr), size(0) {};

        ~Queue() {
            while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        }

        void enqueue(const T& val) {
            Node<T>* newNode = new Node<T>(val);
            if (rear == nullptr) {
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            size++;
        }

        void dequeue() {
            if (front == nullptr) {
                return;
            }
            Node<T>* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            size--;
        } 

        T frontElement() {
            if (front != nullptr) {
               return front->data; 
            }  
        } 

        bool isEmpty() {
            return front == nullptr;
        }

        int getSize() const { return size;}
};

void ferry() {
    double lMeters; 
    int numCars;
    cin >> lMeters >> numCars;
    lMeters *= 100;
    Queue<int> leftQueue, rightQueue;

    for (int i = 0; i < numCars; i++) {
        int carLength; 
        string side; 
        cin >> carLength >> side;

        if (side == "left") {
            leftQueue.enqueue(carLength);
        } else if (side == "right") {
            rightQueue.enqueue(carLength);
        }
    }

    int numTrips = 0;
    bool isLeftBank = true;

    while (!leftQueue.isEmpty() || !rightQueue.isEmpty()) {
        double currentLoad = 0.0;
        bool loadedCar = false;

        if (isLeftBank) {
            while (!leftQueue.isEmpty() && currentLoad + leftQueue.frontElement() <= lMeters) {
                currentLoad += leftQueue.frontElement();
                leftQueue.dequeue();
                loadedCar = true;
            }
        } else {
            while (!rightQueue.isEmpty() && currentLoad + rightQueue.frontElement() <= lMeters) {
                currentLoad += rightQueue.frontElement();
                rightQueue.dequeue();
                loadedCar = true;
            }
        }
        numTrips++;
        isLeftBank = !isLeftBank;
    }
    cout << numTrips << endl;
}

int main() {
    int numCases; cin >> numCases;

    for (int i = 0; i < numCases; i++) {
        ferry();
    }
    return 0;
}