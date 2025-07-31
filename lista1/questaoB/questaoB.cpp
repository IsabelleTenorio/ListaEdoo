#include <iostream>
using namespace std;

//Classe para representar um nó da fila
template <typename T>
class Node {
    public:
        T data; //Dado armazenado no nó
        Node<T>* next; //Ponteiro para o próximo nó
        Node(T data) : data(data), next(nullptr) {}; //Construtor
};

//Classe que implementa uma fila usando lista ligada
template <typename T>
class Queue {
    private:
        Node<T>* front; //Ponteiro para a frente da fila
        Node<T>* rear; //Ponteiro para o final da fila
        int size; //Tamanho da fila

    public:
        Queue() : front(nullptr), rear(nullptr), size(0) {}; //Construtor

        ~Queue() { //Destrutor: remove todos os elementos para evitar vazamento de memória
            while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        }

        void enqueue(const T& val) { //Adiciona elemento no fim da fila
            Node<T>* newNode = new Node<T>(val);
            if (rear == nullptr) { //Se a fila estiver vazia, o novo nó é front e rear
                front = newNode;
                rear = newNode;
            } else { //Conecta novo nó ao final e atualiza o valor de rear
                rear->next = newNode;
                rear = newNode;
            }
            size++;
        }

        void dequeue() { //Remove elemento da frente da fila
            if (front == nullptr) {
                return; //Não remove nada se a fila estiver vazia
            }
            Node<T>* temp = front;
            front = front->next;
            if (front == nullptr) { //Se o último elemento foi removido, rear também é nullptr 
                rear = nullptr;
            }
            delete temp;
            size--;
        } 

        T frontElement() { //Retorna o front da fila
            if (front != nullptr) {
               return front->data; 
            }  
        } 

        bool isEmpty() { //Verifica se a fila está vazia
            return front == nullptr;
        }

        int getSize() const { return size;} //Retorna o tamanho da fila
};

void ferry() { //Função que simula o problema da balsa
    double lMeters; //Tamanho da balsa em m
    int numCars; //Número de carros que querem atravessar a balsa
    cin >> lMeters >> numCars;
    lMeters *= 100; //Converte para cm
    Queue<int> leftQueue, rightQueue; //Filas para carros esperarem em cada lado do rio

    for (int i = 0; i < numCars; i++) { //Lê informações de cada carro e os coloca na fila correspondente
        int carLength; //Tamanho do carro
        string side; //Lado em que está esperando
        cin >> carLength >> side;

        if (side == "left") {
            leftQueue.enqueue(carLength);
        } else if (side == "right") {
            rightQueue.enqueue(carLength);
        }
    }

    int numTrips = 0; //Contador do número de viagens
    bool isLeftBank = true; //Posição atual da balsa (true = lado esquerdo)

    while (!leftQueue.isEmpty() || !rightQueue.isEmpty()) { //Continua simulando até que não haja mais carros em nenhum dos lados
        double currentLoad = 0.0; //Carga atual na balsa (em cm)
        bool loadedCar = false; //Flag para verificar se o carro embarcou

        if (isLeftBank) { //Balsa no lado esquerdo, embarca os carros até que a carga atual da balsa ultrapasse o seu tamanho
            while (!leftQueue.isEmpty() && currentLoad + leftQueue.frontElement() <= lMeters) {
                currentLoad += leftQueue.frontElement();
                leftQueue.dequeue();
                loadedCar = true;
            }
        } else { //Balsa no lado direito
            while (!rightQueue.isEmpty() && currentLoad + rightQueue.frontElement() <= lMeters) {
                currentLoad += rightQueue.frontElement();
                rightQueue.dequeue();
                loadedCar = true;
            }
        }
        numTrips++;
        isLeftBank = !isLeftBank; //Balsa muda de lado
    }
    cout << numTrips << endl;
}

int main() {
    int numCases; cin >> numCases; //Número de casos que atravessarão balsas

    for (int i = 0; i < numCases; i++) { //Processa cada caso
        ferry();
    }
    return 0;
}