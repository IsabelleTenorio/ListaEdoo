#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(T data) : data(data), next(nullptr) {}
};

template <typename K, typename V>
struct PairKeyValue {
    long long key;
    V value;
};

template <typename K, typename V>
class HashTable {
  private:
    Node<PairKeyValue<K, V>>** table;
    int count;
    int capacity;

    template <typename KeyType = long long >
    typename enable_if<is_same<KeyType, string>::value, unsigned int>::type
    hashFunction(KeyType key) {
      unsigned long hash = 5381;
      
      for (char c : key) {
        hash = ((hash << 5) + hash) + c; 
      }
      return hash % capacity;
    }

    template <typename KeyType = long long >
    typename enable_if<is_integral<KeyType>::value, unsigned int>::type
    hashFunction(KeyType key) {
      return (static_cast<unsigned long long>(key) * 2654435761) % capacity;
    }

  public:
    HashTable(int capacity = 199999) : capacity(capacity), count(0) {
        table = new Node<PairKeyValue<K, V>>*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
      for (int i = 0; i < capacity; ++i) {
        Node<PairKeyValue<K, V>>* current = table[i];

        while (current != nullptr) {
          Node<PairKeyValue<K, V>>* temp = current;
          current = current->next;
          delete temp;
        }
      }
      delete[] table;
    }

    void insert(const long long& key, const V& value) {
      unsigned int index = hashFunction(key);
      Node<PairKeyValue<K, V>>* entry = table[index];
      Node<PairKeyValue<K, V>>* previous = nullptr;

      while (entry != nullptr) {
        if (entry->data.key == key) {
          entry->data.value = value;
          return;
        }
        previous = entry;
        entry = entry->next;
      }
      PairKeyValue<K, V> newPair = {key, value};
      Node<PairKeyValue<K, V>>* newNode = new Node<PairKeyValue<K, V>>(newPair);

      if (previous == nullptr) {
        table[index] = newNode; 
      } else {
        previous->next =  newNode;
      }
      count++;
    }

    V get(const long long& key) {
      unsigned int index = hashFunction(key);
      Node<PairKeyValue<K, V>>* entry = table[index];
      
      while (entry != nullptr) {
        if (entry->data.key == key) {
          return entry->data.value;
        }
        entry = entry->next;
      }
      return 0; 
    }

    bool containsKey(const long long& key) {
      unsigned int index = hashFunction(key);
      Node<PairKeyValue<K, V>>* entry = table[index];

      while (entry != nullptr) {
        if (entry->data.key == key) {
          return true;
        }
        entry= entry->next;
      }
      return false;
    }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<long long> values(26);

  for (int i = 0; i < 26; i++) {
    cin >> values[i];
  }

  string s; cin >> s;
  vector<HashTable<long long, int>> counts(26);
  long long currentPrefixSum = 0, answer = 0;

  for (char c : s) {
    int charIndex = c - 'a';
    HashTable<long long, int>& charTable = counts[charIndex];

    answer += charTable.get(currentPrefixSum);

    currentPrefixSum += values[charIndex];
    long long currentCount = charTable.get(currentPrefixSum);
    charTable.insert(currentPrefixSum, currentCount + 1);
  }

  cout << answer << endl;
  return 0;
}