#include <iostream>
using namespace std;
class HashTable {
private:
    int *table;
    int size;

public:
    HashTable(int s) {
        size = s;
        table = new int[size];
        for (int i = 0; i < size; i++)
            table[i] = -1;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int index = hashFunction(key);
        while (table[index] != -1) {
            index = (index + 1) % size;
        }
        table[index]= key;
        cout << "Inserted " << key <<" at index " << index << endl;
    }

    void search(int key) {
        int index = hashFunction(key);
        int start = index;
        while (table[index] != -1) {
            if (table[index] == key) {
                cout << "Key " << key << " found at index " << index << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
        cout << "Key " << key << " not found" << endl;
    }

    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < size; i++) {
            if (table[i] == -1)
                cout << i << " - Empty \n";
            else
                cout << i << " - " << table[i] << endl;
        }
    }
};

int main() {
    HashTable ht(10);

    ht.insert(23);
    ht.insert(33);
    ht.insert(43); // collision case here
    ht.insert(13);

    ht.display();

    ht.search(33);
    ht.search(99);

    return 0;
}