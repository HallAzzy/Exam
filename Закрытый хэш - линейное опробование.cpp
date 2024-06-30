#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char key;
    bool occupied;
    Node(char k) : key(k), occupied(true) {}
    Node() : key('.'), occupied(false) {} // ����������� �� ���������
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
    vector<Node> hash_table(M); // �������������� ������ Node
    char key;
    vector<char> keys(10);

    // ���� ������
    for (int i = 0; i < 10; i++) {
        cin >> key;
        keys[i] = key;
    }

    // ������� ������ � ���-�������
    int count = 0; // ������� ����������� ������
    int inserted[10];
    for (int i = 0; i < 10; i++) {
        inserted[i] = 0;
    }
    while (count < 10) {
        for (int i = 0; i < 10; i++) {
            if (inserted[i] == 0) { // ���������, �������� �� ����
                int index = hash_function(keys[i], M);
                int attempt = 0;

                while (hash_table[index].occupied) {
                    index = linear_probe(index, M, attempt);
                    attempt++;
                    if (attempt >= M) {
                        attempt = 0; // ������������ � ������ �������
                    }
                }

                hash_table[index] = Node(keys[i]);
                inserted[i] = 1; // �������� ���� ��� �����������
                count++; // ����������� ������� ����������� ������
            }
        }
    }

    // ����� ���-�������
    for (int i = 0; i < M; i++) {
        if (hash_table[i].occupied) {
            cout << "������ " << i << ": " << hash_table[i].key << endl;
        }
        else {
            cout << "������ " << i << ": ." << endl;
        }
    }

    return 0;
}
/*��������� ���������� ���-�������, ������������ ���������
��������� � ������� E A S Y Q U T I O N � ��������� ������� �
������������� ������ ������� �������� M= 16, ������������
�������� ������������ (�����������). ��� �������������� k-�� �����
�������� � ������ ������� ����������� ���-������� 11k mod �.*/