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
class LinkedList {
    private:
        Node<T>* head;
        int size;
    
    public:
        LinkedList(): head(nullptr), size(0) {}

        ~LinkedList() {
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void insert(const T& data) {
            Node<T>* newNode = new Node<T>(data);
            newNode->next = head;
            head = newNode;
            size++;
        }

        void append(const T& data) {
            Node<T>* newNode = new Node<T>(data);

            if (head == nullptr) {
                head = newNode;
            } else {
                Node<T>* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            size++;
        }

        bool remove(const T& data) {
            if (head == nullptr) {return false;}

            if (head->data == data) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                size--;
                return true;
            }

            Node<T>* current = head;
            while (current->next != nullptr && current->next->data != data) {
                current = current->next;
            }

            if (current->next == nullptr) {return false;}

            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
            return true;
        }

        void display() {
            Node<T>* current = head;
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
        }

        int getSize() {return size;}
};