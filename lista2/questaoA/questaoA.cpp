#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 101; 

struct HashNode {
  string key;
  bool isOccupied;
  HashNode():isOccupied(false) {}
};

int calculateHash(const string& key) {
  long long hash = 0;
  for (int i = 0; i < key.length(); ++i) {
    hash += (long long)key[i] * (i + 1);
  }
  return (19 * hash) % TABLE_SIZE;
}

class HashTable {
  private:
    vector<HashNode> table;
    int count;

    int findKey(const string& key) {
      int hash = calculateHash(key);
      for (int j = 0; j < 20; ++j) {
        int index = (hash + j * j + 23 * j) % TABLE_SIZE;
        if (table[index].isOccupied && table[index].key == key) {
          return index;
        }
      }
      return -1;
    }

  public:
    HashTable() : table(TABLE_SIZE), count(0) {}

    void insert(const string& key) {
      if (findKey(key) != -1) {
        return; 
      }

      int hash = calculateHash(key);
      for (int j = 0; j < 20; ++j) {
        int index = (hash + j * j + 23 * j) % TABLE_SIZE;
        if (!table[index].isOccupied) {
          table[index].key = key;
          table[index].isOccupied = true;
          count++;
          return;
        }
      }
    }

    void del(const string& key) {
      int index = findKey(key);
      if (index != -1) {
        table[index].isOccupied = false;
        count--;
      }
    }

    void print() {
      cout << count << endl;
      for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].isOccupied) {
          cout << i << ":" << table[i].key << endl;
        }
      }
    }
};

void solve() {
  int n;
  cin >> n;

  HashTable ht;
  for (int i = 0; i < n; ++i) {
    string op;
    cin >> op;
    string key = op.substr(4);
    if (op.substr(0, 3) == "ADD") {
      ht.insert(key);
    } else {
      ht.del(key);
    }
  }
  ht.print();
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}