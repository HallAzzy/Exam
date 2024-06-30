/*Приведите содержимое хеш-таблицы, образованной вставками
элементов с ключами E A S Y Q U T I O N в указанном порядке в
первоначально пустую таблицу размером M= 16, использующую
линейное исследование (опробование). Для преобразования k-ой буквы
алфавита в индекс таблицы используйте хеш-функцию 11k mod М.*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char key;
    bool occupied;
    Node(char k) : key(k), occupied(true) {}
    Node() : key('.'), occupied(false) {} // Конструктор по умолчанию
};

int hash_function(char key, int M) {
    int k = key - 'A' + 1;
    return (11 * k) % M;
}

int linear_probe(int index, int M, int attempt) {
    return (index + attempt) % M;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int M = 16;
    vector<Node> hash_table(M); // Инициализируем вектор Node
    char key;
    vector<char> keys(10);

    // Ввод ключей
    for (int i = 0; i < 10; i++) {
        cin >> key;
        keys[i] = key;
    }

    // Вставка ключей в хеш-таблицу
    int count = 0; // Счетчик вставленных ключей
    int inserted[10];
    for (int i = 0; i < 10; i++) {
        inserted[i] = 0;
    }
    while (count < 10) {
        for (int i = 0; i < 10; i++) {
            if (inserted[i] == 0) { // Проверяем, вставлен ли ключ
                int index = hash_function(keys[i], M);
                int attempt = 0;

                while (hash_table[index].occupied) {
                    index = linear_probe(index, M, attempt);
                    attempt++;
                    if (attempt >= M) {
                        attempt = 0; // Возвращаемся к началу таблицы
                    }
                }

                hash_table[index] = Node(keys[i]);
                inserted[i] = 1; // Отмечаем ключ как вставленный
                count++; // Увеличиваем счетчик вставленных ключей
            }
        }
    }

    // Вывод хеш-таблицы
    for (int i = 0; i < M; i++) {
        if (hash_table[i].occupied) {
            cout << "Индекс " << i << ": " << hash_table[i].key << endl;
        }
        else {
            cout << "Индекс " << i << ": ." << endl;
        }
    }

    return 0;
}
