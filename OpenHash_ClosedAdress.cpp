#include <iostream>

using namespace std;
class OpenHashTable {
private:
    struct Node {
        char key;
        int value;
        Node* next;

        Node( char key,  int value) : key(key), value(value), next(nullptr) {}
    };

    Node** table;
    size_t capacity;

    // Хеш-функция (простая, можно использовать другую)
    size_t hash( char key) {
        return (key-'a') % capacity;
    }

public:
    OpenHashTable(size_t capacity) : capacity(capacity) {
        table = new Node*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    ~OpenHashTable() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }

    // Вставка элемента
    void insert(char key, int value) {
        size_t index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Поиск элемента по ключу
    int* find(char key) {
        size_t index = hash(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Удаление элемента по ключу
    void erase(char key) {
        size_t index = hash(key);
        Node* previous = nullptr;
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    table[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
    void print(){
        for (int i=0;i<capacity;i++){
            if(table[i]== nullptr){
                cout<<i+1<<" -"<<endl;
            }
            else{
                cout<<i+1;
                Node *obj=table[i];
                while(obj!= nullptr){
                    cout<<" "<<obj->key<<" "<<obj->value<<" | ";
                    obj=obj->next;
                }
                cout<<endl;
            }
        }
    }
};

int main() {
    OpenHashTable ht(10);

    ht.insert('a',1);
    ht.insert('b', 2);
    ht.insert('c', 3);

    std::cout << "Value for key ф: " << *ht.find('a') << std::endl;

    ht.erase('a');

    if (ht.find('a') == nullptr) {
        std::cout << "Key a not found" << std::endl;
    }
    std::cout << "Value for key b: " << *ht.find('b') << std::endl;
    ht.print();
    return 0;
}
