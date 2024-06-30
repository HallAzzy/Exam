#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Односвязный список для хранения элементов в методе цепочек
struct listNode {
    char key;
    int hashedKey;
    listNode* next;

    listNode(char _key, int _hashedKey) : key(_key), hashedKey(_hashedKey), next(nullptr) {
    }
};

struct list {
    listNode* first;
    listNode* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(char key, int hashedKey) {
        listNode* p = new listNode(key, hashedKey);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (is_empty()) return;
        listNode* p = first;
        while (p) {
            cout << "(" << p->key << ", " << p->hashedKey << ") ";
            p = p->next;
        }
        cout << endl;
    }

    listNode* find(char key) {
        listNode* p = first;
        while (p && p->key != key)
            p = p->next;
        return (p && p->key == key) ? p : nullptr;
    }

    void remove(char key) {
        if (is_empty()) return;
        if (first->key == key) {
            listNode* p = first;
            first = p->next;
            delete p;
            return;
        }
        listNode* slow = first;
        listNode* fast = first->next;
        while (fast && fast->key != key) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "Element with key " << key << " does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
};

// Класс для открытого хэширования с использованием метода цепочек (закрытая адресация)
class OpenHash {
private:
    int size;
    list* hashTable;

    int hash(char key) {
        return 11 * (key - 'A' + 1) % size; // Для работы с нижним регистром исправить 'A' на 'a'
    }

public:
    OpenHash(int _size) : size(_size) { // Создание массива списков
        hashTable = new list[size];
    }

    ~OpenHash() {
        delete[] hashTable;
    }

    void add(char key) {
        int hashedKey = hash(key);
        hashTable[hashedKey].push_back(key, hashedKey);
    }

    void remove(char key) {
        int hashedKey = hash(key);
        hashTable[hashedKey].remove(key);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << "Hash[" << i << "]: ";
            hashTable[i].print();
        }
    }

    string at(char key) {
        int hashedKey = hash(key);
        listNode* node = hashTable[hashedKey].find(key);
        if (node)
            return "Element with key " + string(1, key) + " found at hash " + to_string(hashedKey);
        else
            return "Element with key " + string(1, key) + " not found";
    }
};

int main() {
    OpenHash hashTable(16);  // Пример из мудла

    hashTable.add('E');
    hashTable.add('A');
    hashTable.add('S');
    hashTable.add('Y');
    hashTable.add('Q');
    hashTable.add('U');
    hashTable.add('T');
    hashTable.add('I');
    hashTable.add('O');
    hashTable.add('N');

    hashTable.print();

    hashTable.remove('A');
    hashTable.remove('Q');

    hashTable.print();

    cout << "Value at key E: " << hashTable.at('E') << endl;
    cout << "Value at key A: " << hashTable.at('A') << endl;

    return 0;
}
