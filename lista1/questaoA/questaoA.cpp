#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class Stack {
    private:
        Node<T>* topNode; 
    
    public:
        Stack() : topNode(nullptr) {} 

        ~Stack() { 
            while (!isEmpty()) {
                pop();
            }
        } 
        
        bool isEmpty() const {
            return topNode == nullptr;
        } 

        void push(T data) {
            Node<T>* newNode = new Node<T>(data); 
            newNode->next = topNode;
            topNode = newNode;
        } 

        void pop() {
            if (isEmpty()) {
                cout << "Stack is empty, unable to pop." << endl;
                return;
            }
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        } 

        T top() const {
            if (isEmpty()) {
                cout << "Stack is empty, unable to see the top." << endl;
                return T(); 
            }
            return topNode->data;
        }    
};


string isBalanced(const string& sequence) {
    Stack<char> brackets;

    for (char character : sequence) {
        if (character == '{' || character == '[' || character == '(') {
            brackets.push(character);
        } else if (character == '}' || character == ']' || character == ')') {
            if (brackets.isEmpty()) {
                return "NO"; 
            }

            char topChar = brackets.top();

            if ((character == '}' && topChar == '{') || (character == ']' && topChar == '[') || (character == ')' && topChar == '(')) {
                brackets.pop();
            } else {
                return "NO"; 
            }
        }
    }

    return brackets.isEmpty() ? "YES" : "NO"; 
}


int main() {
    int n; cin >> n; 

    for (int i = 0; i < n; i++) {
        string sequence; cin >> sequence; 
        cout << isBalanced(sequence) << endl; 
    }

    return 0; 
}