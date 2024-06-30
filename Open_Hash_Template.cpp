#include <iostream>

template <typename Key, typename Value>
class OpenHashTable {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {}
    };

    Node** table;
    size_t capacity;

    // Хеш-функция (простая, можно использовать другую)
    size_t hash(const Key& key) {
        return key % capacity;
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
    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Поиск элемента по ключу
    Value* find(const Key& key) {
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
    void erase(const Key& key) {
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
};

int main() {
    OpenHashTable<int, std::string> ht(10);

    ht.insert(1, "One");
    ht.insert(11, "Eleven");
    ht.insert(21, "Twenty-one");

    std::cout << "Value for key 11: " << *ht.find(11) << std::endl;

    ht.erase(11);

    if (ht.find(11) == nullptr) {
        std::cout << "Key 11 not found" << std::endl;
    }
    std::cout << "Value for key 11: " << *ht.find(21) << std::endl;
    return 0;
}
