#include <iostream>
#include <iomanip>
#include <set>
#include <cctype>
using namespace std;

template <typename T>
class Node {
    public:
        T element;
        Node<T>* next;
        Node(const T& element, Node<T>* next = NULL) : element(element), next(nullptr) {};
        Node(Node<T>* next = NULL) : next(next) {};
};

template <typename T>
class LinkedList : public Node<T> {
    private:
        Node<T>* head;
        Node<T>* tail;
        Node<T>* current;
        int size;

        void init() {
            current = tail = head = new Node<T>;
            size = 0;
        }

        void removeALL() {
            while (head != NULL) {
                current = head;
                head = head->next;
                delete current;
            }
        }

    public:
        LinkedList() { init();}
        ~LinkedList() { removeALL(); }

        void clear() {removeALL(); init();}

        void insert(const T& data) {
            current->next = new Node<T>(data, current->next);

            if (tail == current) {
                tail = current->next;
            }
            size++;
        }

        void append(const T& data) {
            tail = tail->next = new Node<T>(data, NULL);
            size++;
        }

        T remove() {
            T data = current->next->element;
            Node<T>* temp = current->next;

            if (tail == current->next) {
                tail = current;
            }
            current->next = current->next->next;
            delete temp;
            size--;
            return data;
        }

        void moveToStart() {
            current = head;
        }

        void moveToEnd() {
            current = tail;
        }

        void prev() {
            if (current == head) {
                return;
            }
            Node<T>* temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            current = temp;
        }

        void next() {
            if (current->next != NULL) {
                current = current->next;
            }
        }

        int length() const {
            return size;
        }

        int currPos() const {
            Node<T>* temp = head;
            int i;

            for (i = 0; temp != current; i++) {
                temp = temp->next;
            }
            return i;
        }

        void moveToPos(int pos) {
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        }

        const T& getValue() const {
            return current->next->element;
        }

        bool contains(const T& data) const {
            Node<T>* temp = head->next;
            while (temp != nullptr) {
                if (temp->element == data) {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
};

void printHeader() {
    cout << "+----------+----------------+-----------------------------+\n";
    cout << "| Keyboard | # of printable | Additionally, the following |\n";
    cout << "|          |      lines     |  letter keys can be broken  |\n";
    cout << "+----------+----------------+-----------------------------+\n";
}

void printSeparator() {
    cout << "+----------+----------------+-----------------------------+\n";
}

void printKey(const int& key) {
    cout << "|   " << right << setw(3) << key << "    |      ";
}

void printLine(const int& line) {
    cout << right << setw(3) << line << "       | ";
}

void printBrokenKeys(const string& brokenKeys) {
    cout << left << setw(28) << brokenKeys << "|\n";
}

int main() {
    printHeader();

    int keyboardNum = 1;
    string brokenKeysInput;

    while (cin >> brokenKeysInput && brokenKeysInput != "finish") {
        LinkedList<char> brokenKeysList;
        for (char characters : brokenKeysInput) {
            if (isalpha(characters)) {
                brokenKeysList.append(tolower(characters));
            }
        }

        int printableLines = 0;
        set<char> allUsedLetters;

        string lineContent;
        LinkedList<string> textLines;
        while (getline(cin >> ws, lineContent)) {
            if (lineContent != "END") {
                textLines.append(lineContent);    
            } else {
                textLines.append(lineContent);
                break;
            }
            
        }

        textLines.moveToStart();
        for (int i = 0; i < textLines.length(); ++i) {
            string currentLine = textLines.getValue();
            textLines.next();

            LinkedList<char> lineLetters;
            bool canTypeLine = true;

            for (char character : currentLine) {
                if (isalpha(character)) {
                    char lowerChar = tolower(character);
                    
                    if (!lineLetters.contains(lowerChar)) {
                        lineLetters.append(lowerChar);
                    }

                    if (brokenKeysList.contains(lowerChar)) {
                        canTypeLine = false;
                    }
                }
            }

            if (canTypeLine) {
                printableLines++;
                lineLetters.moveToStart();
                for (int j = 0; j < lineLetters.length(); ++j) {
                    allUsedLetters.insert(lineLetters.getValue());
                    lineLetters.next();
                }
            }
        }

        string additionalBrokenKeys = "";
        for (char character = 'a'; character <= 'z'; ++character) {
            if (!brokenKeysList.contains(character) && allUsedLetters.find(character) == allUsedLetters.end()) {
                additionalBrokenKeys += character;
            }
        }

        printKey(keyboardNum);
        printLine(printableLines);
        printBrokenKeys(additionalBrokenKeys);
        printSeparator();

        keyboardNum++;
    }

    return 0;
    
}