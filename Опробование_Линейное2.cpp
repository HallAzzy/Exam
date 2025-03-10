/*Напишите программу, которая вставляет N/2случайных целых чисел в таблицу
размером N, использующую линейное опробование, а затем на основании длин кластеров
вычисляет средние затраты на неудачный поиск в результирующей таблице, для N= 10^3, 10^4, 10^5 и 10^6.*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key;
    bool occupied;
    Node() : key(-1), occupied(false) {}
};

int hash_function(int key, int M) {
    return key % M; // Простейшая хеш-функция
}

int linear_probe(int index, int M, int attempt) {
    return (index + attempt) % M;
}

double calculate_average_search_cost(vector<Node>& hash_table, int N) {
    double total_cost = 0;
    int cluster_size = 0;
    int cluster_count = 0;

    for (int i = 0; i < N; i++) {
        if (hash_table[i].occupied) {
            cluster_size++;
        }
        else {
            if (cluster_size > 1) {
                total_cost += cluster_size * (cluster_size + 1) / 2; // Кластеризация
                cluster_count++;
            }
            cluster_size = 0;
        }
    }

    double average_cost = total_cost / cluster_count;
    return average_cost;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0)); // Инициализация генератора случайных чисел

    int sizes[] = { 1000, 10000, 100000, 1000000 };

    for (int N : sizes) {
        vector<Node> hash_table(N);
        vector<int> keys(N / 2);

        // Вставка N/2 случайных чисел в таблицу
        for (int i = 0; i < N / 2; i++) {
            int key = rand() % (2 * N); // Генерация случайного числа
            int index = hash_function(key, N);
            int attempt = 0;

            while (hash_table[index].occupied) {
                attempt++;
                index = linear_probe(index, N, attempt);
            }

            hash_table[index].key = key;
            hash_table[index].occupied = true;
            keys[i] = key;
        }

        double avg_search_cost = calculate_average_search_cost(hash_table, N);
        cout << "Средние затраты на неудачный поиск в таблице размером " << N << ": " << avg_search_cost << endl;
    }

    return 0;
}
