#include <iostream>
using namespace std;

//Classe para representar um nó da lista ligada
template <typename T>
class Node {
public:
    T data; //Dado armazenado no nó
    Node<T>* next; //Ponteiro para o próximo nó
    Node(T data) : data(data), next(nullptr) {} //Construtor
};

//Classe que implementa uma pilha usando lista ligada
template <typename T>
class Stack {
    private:
        Node<T>* topNode; //Ponteiro para o nó do topo da pilha
    
    public:
        Stack() : topNode(nullptr) {} //Construtor: inicializa uma pilha vazia

        ~Stack() { //Destrutor: remove todos os elementos da pilha para evitar vazamento de memória
            while (!isEmpty()) {
                pop();
            }
        } 
        
        bool isEmpty() const { //Verifica se a pilha está vazia
            return topNode == nullptr;
        } 

        void push(T data) { //Adiciona um elemento no topo 
            Node<T>* newNode = new Node<T>(data); //Cria novo nó
            newNode->next = topNode; //Novo nó aponta para o antigo topo
            topNode = newNode; //Novo nó se torna o topo
        } 

        void pop() { //Remove o elemento do topo
            if (isEmpty()) {
                cout << "Stack is empty, unable to pop." << endl;
                return;
            }
            Node<T>* temp = topNode; //Guarda referência do nó a ser removido
            topNode = topNode->next; //Topo passa a ser o próximo nó
            delete temp; //Libera memória do nó removido
        } 

        T top() const { //Retorna o elemento do topo sem removê-lo
            if (isEmpty()) {
                cout << "Stack is empty, unable to see the top." << endl;
                return T(); //Retorna valor padrão do tipo T
            }
            return topNode->data;
        }    
};

//Função que verifica se uma sequência de parênteses/colchetes/chaves está balanceada
string isBalanced(const string& sequence) {
    Stack<char> brackets;

    for (char character : sequence) { //Percorre cada caractere da sequência
        if (character == '{' || character == '[' || character == '(') { //Empilha se for um caractere de abertura
            brackets.push(character);

        } else if (character == '}' || character == ']' || character == ')') { //Se for um caractere de fechamento, verifica se são correspondentes
            if (brackets.isEmpty()) { //Se a pilha estiver vazia, não há caractere correspondente
                return "NO"; 
            }

            char topChar = brackets.top(); //Pega o último caractere de abertura

            if ((character == '}' && topChar == '{') || (character == ']' && topChar == '[') || (character == ')' && topChar == '(')) {
                brackets.pop(); //Verifica se o fechamento corresponde à abertura e remove a abertura correspondente
            } else {
                return "NO"; //Se o fechamento não for correspondente
            }
        }
    }
    // Se a pilha estiver vazia, todos os parênteses foram balanceados corretamente
    // Se a pilha não estiver vazia, há aberturas sem fechamento correspondente
    return brackets.isEmpty() ? "YES" : "NO"; //
}


int main() {
    int n; cin >> n; //Lê o número de sequências a serem testadas

    for (int i = 0; i < n; i++) { //Testa cada sequência
        string sequence; cin >> sequence; //Lê a sequência
        cout << isBalanced(sequence) << endl; //Verifica e imprime resultado
    }

    return 0; 
}