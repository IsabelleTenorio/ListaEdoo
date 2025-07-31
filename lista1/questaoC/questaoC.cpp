#include <iostream>
#include <iomanip>
#include <set>
#include <cctype>
using namespace std;

//Classe para representar um nó da lista ligada
template <typename T>
class Node {
    public:
        T element; //Elemento armazenado no nó
        Node<T>* next; //Ponteiro para o próximo nó
        Node(const T& element, Node<T>* next = NULL) : element(element), next(nullptr) {}; //Construtor com elemento e próximo nó
        Node(Node<T>* next = NULL) : next(next) {}; //Construtor apenas com o próximo nó
};

//Classe template que implementa uma lista ligada com ponteiro para a posição atual
template <typename T>
class LinkedList : public Node<T> {
    private:
        Node<T>* head; //Ponteiro para o nó cabeça
        Node<T>* tail; //Ponteiro para o último nó
        Node<T>* current; //Ponteiro para a posição atual
        int size; //Tamnho da lista

        void init() { //Inicializa a lista vazia com uma head
            current = tail = head = new Node<T>;
            size = 0;
        }

        void removeALL() { //Remove todos os nós
            while (head != NULL) {
                current = head;
                head = head->next;
                delete current;
            }
        }

    public:
        LinkedList() { init();} //Construtor
        ~LinkedList() { removeALL(); } //Destrutor

        void clear() {removeALL(); init();} //Limpa a lista e reinicializa

        void insert(const T& data) { //Insere elemento na posição atual do ponteiro current
            current->next = new Node<T>(data, current->next);

            if (tail == current) { //Se o cursor estava no final, atualiza a tail
                tail = current->next;
            }
            size++;
        }

        void append(const T& data) { //Adiciona elemento no final da lista
            tail = tail->next = new Node<T>(data, NULL);
            size++;
        }

        T remove() { //Remove e retorna o elemento na posição seguinte ao cursor
            T data = current->next->element;
            Node<T>* temp = current->next;

            if (tail == current->next) { //Se removendo o último elemento, atualiza tail
                tail = current;
            }
            current->next = current->next->next;
            delete temp;
            size--;
            return data;
        }

        void moveToStart() { //Move o current para o início (head)
            current = head;
        }

        void moveToEnd() { //Move o current para o final
            current = tail;
        }

        void prev() { //Move o current para a posição anterior
            if (current == head) {
                return; //Se já estiver no início
            }
            Node<T>* temp = head;
            while (temp->next != current) { //Encontra o nó anterior ao current
                temp = temp->next;
            }
            current = temp;
        }

        void next() {
            if (current->next != NULL) { //Move o current para a próxima posição
                current = current->next;
            }
        }

        int length() const { //Retorna o tamanho da lista
            return size;
        }

        int currPos() const { //Retorna a posição atual do current
            Node<T>* temp = head;
            int i;

            for (i = 0; temp != current; i++) {
                temp = temp->next;
            }
            return i;
        }

        void moveToPos(int pos) { //Move o current para uma posição específica
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        }

        const T& getValue() const { //Retorna o valor do elemento na posição seguinte ao current
            return current->next->element;
        }

        bool contains(const T& data) const { //Verifica se a lista contém um determinado elemento
            Node<T>* temp = head->next; //Pula a head
            while (temp != nullptr) {
                if (temp->element == data) {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
};

void printHeader() { //Função para imprimir o cabeçalho da tabela de resultados
    cout << "+----------+----------------+-----------------------------+\n";
    cout << "| Keyboard | # of printable | Additionally, the following |\n";
    cout << "|          |      lines     |  letter keys can be broken  |\n";
    cout << "+----------+----------------+-----------------------------+\n";
}

void printSeparator() { //Função para imprimir o separador da tabela
    cout << "+----------+----------------+-----------------------------+\n";
}

void printKey(const int& key) { //Função para imprimir o número do teclado na tabela
    cout << "|   " << right << setw(3) << key << "    |      ";
}

void printLine(const int& line) { //Função para imprimir o número de linhas imprimíveis
    cout << right << setw(3) << line << "       | ";
}

void printBrokenKeys(const string& brokenKeys) { //Função para imprimir as teclas quebradas adicionais
    cout << left << setw(28) << brokenKeys << "|\n";
}

int main() { 
    printHeader();

    int keyboardNum = 1; //Contador de teclados
    string brokenKeysInput;

    while (cin >> brokenKeysInput && brokenKeysInput != "finish") { //Loop principal: processa cada teclado até encontrar "finish"
        LinkedList<char> brokenKeysList; //Lista para armazenar as teclas quebradas
        for (char characters : brokenKeysInput) { //Extrai apenas as letras das teclas quebradas e converte para minúscula
            if (isalpha(characters)) {
                brokenKeysList.append(tolower(characters));
            }
        }

        int printableLines = 0; //Contador de linhas digitáveis
        set<char> allUsedLetters; //Set com todas as letras usadas nas linhas válidas

        string lineContent; //Conteúdo de cada linha
        LinkedList<string> textLines; //Lista para armazenar as linhas
        cin.ignore();
        while (getline(cin, lineContent)) { //Lê todas as linhas até encontrar "END"
            if (lineContent != "END") { 
                textLines.append(lineContent);    
            } else {
                textLines.append(lineContent); //"END" também deve ser adicionado antes da quebra do loop
                break;
            }
            
        }

        textLines.moveToStart(); //Processa cada linha para verificar se pode ser digitada
        for (int i = 0; i < textLines.length(); ++i) {
            string currentLine = textLines.getValue();
            textLines.next();

            LinkedList<char> lineLetters; //Letras únicas da linha atual
            bool canTypeLine = true; //Flag para verificar se a linha pode ser digitada

            for (char character : currentLine) { //Analisa cada caractere da linha
                if (isalpha(character)) {
                    char lowerChar = tolower(character);
                    
                    if (!lineLetters.contains(lowerChar)) { //Adiciona letra à lista se ainda não estiver presente
                        lineLetters.append(lowerChar);
                    }


                    if (brokenKeysList.contains(lowerChar)) { //Se a letra está nas teclas quebradas, linha não pode ser digitada
                        canTypeLine = false;
                    }
                }
            }

            if (canTypeLine) { //Se a linha pode ser digitada, conta ela e adiciona suas letras ao set geral
                printableLines++;
                lineLetters.moveToStart();
                for (int j = 0; j < lineLetters.length(); ++j) {
                    allUsedLetters.insert(lineLetters.getValue());
                    lineLetters.next();
                }
            }
        }

        string additionalBrokenKeys = "";
        for (char character = 'a'; character <= 'z'; ++character) { //Encontra teclas adicionais que podem estar quebradas
            if (!brokenKeysList.contains(character) && allUsedLetters.find(character) == allUsedLetters.end()) { //Se letra não está quebrada E não foi usada nas linhas válidas
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