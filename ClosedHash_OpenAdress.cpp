// Закрытое хэширование

#include <vector>
#include <iostream>

using namespace std;

struct HashTable {
    struct Node {
        char key;
        bool check;

        Node(char _key) : key(_key), check(false) {}
    };

    int count;
    Node** table;

    HashTable(int capacity) : count(capacity) {
        table = new Node * [capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < count; ++i) {
            Node* current = table[i];
            delete current;
        }
        delete[] table;
    }

    int hash(char key) {
        int value = 11 * (key) % count;
        return value;
    }

    void insert(char key) {
        Node* newNode = new Node(key);
        int hash_key = hash(key);
        for (int i = 0; i < count; i++) {
            int val = (11 * (key) + i) % count;
            if (table[val] == nullptr) {
                table[val] = newNode;
                return;
            }

            if (table[val]->check == true) {
                table[val]->key = key;
                table[val]->check=false;
                return;
            }
        }
        return;
    }

    void print() {//доделать проверку на check вдруг удалённый элемент
        for (int i = 0; i < count; ++i) {
            if (table[i] == nullptr)
                cout << " NOTHING " << i << endl;
            else
                cout << table[i]->key << " AT " << i << endl;
        }
    }
    void find(char key){
        for(int i=0;i<count;i++){
            int val = (11 * (key) + i) % count;
            if (table[val]== nullptr) {
                return;
            }
            if ((table[val]->key==key)&&(table[val]->check==false)){
                cout<<"index:"<<val<<"key:"<<key<<endl;
            }
        }
        return;
    }
};

int main() {
    HashTable h(16);
    h.insert('E');
    h.insert('A');
    h.insert('S');
    h.insert('Y');
    h.insert('Q');
    h.insert('U');
    h.insert('T');
    h.insert('I');
    h.insert('O');
    h.insert('N');
    h.print();
    h.find('A');
}
