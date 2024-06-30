#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];

    bool endOfWord;

    char letter;

    TrieNode()
    {
        endOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
        }
        letter = '\0';
    }

    ~TrieNode()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (children[i] != NULL)
            {
                delete children[i];
            }
        }
    }
};

class Trie
{
public:

    TrieNode root;

    void insert(string str) // Вставка в дерево слова
    {
        TrieNode* current = &root;
        for (size_t i = 0; i < str.size(); i++)
        {
            if (current->children[str.at(i) - 'a'] == NULL)
            {
                current->children[str.at(i) - 'a'] = new TrieNode;
                current->children[str.at(i) - 'a']->letter = str.at(i);
            }
            current = current->children[str.at(i) - 'a'];
        }
        current->endOfWord = true;
    }

    TrieNode* search(string str) // Поиск слова в дереве
    {
        TrieNode* current = &root;
        for (size_t i = 0; i < str.size(); i++)
        {
            if (current->children[str.at(i) - 'a'])
            {
                current = current->children[str.at(i) - 'a'];
            }
            else
            {
                current = NULL;
                break;
            }
        }
        return current;
    }

    void collectWords(TrieNode* node, string prefix, vector<string>& words) // Рекурсивный метод, используемый ниже
    {
        if (node->endOfWord)
        {
            words.push_back(prefix);
        }
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (node->children[i] != NULL)
            {
                collectWords(node->children[i], prefix + node->children[i]->letter, words);
            }
        }
    }

    vector<string> getAllWords() // Получение всех слов в массив
    {
        vector<string> words;
        collectWords(&root, "", words);
        return words;
    }

    void removeWord(TrieNode* node, string str, int depth = 0) // Удаление слова с подстрокой
    {
        if (!node) return;

        if (depth == str.size())
        {
            if (node->endOfWord)
            {
                node->endOfWord = false;
            }
            return;
        }

        int index = str[depth] - 'a';
        if (node->children[index])
        {
            removeWord(node->children[index], str, depth + 1);

            // Проверка, можно ли удалить этот узел
            bool isEmpty = true;
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (node->children[i])
                {
                    isEmpty = false;
                    break;
                }
            }
            if (isEmpty && !node->endOfWord)
            {
                delete node->children[index];
                node->children[index] = NULL;
            }
        }
    }

    void removeWordsWithSubstring(string substring) // Удаление всех слов с данной подстрокой
    {
        vector<string> allWords = getAllWords();
        for (const string& word : allWords)
        {
            if (word.find(substring) != string::npos)
            {
                removeWord(&root, word);
            }
        }
    }

    // Метод для печати дерева
    void printTrie(TrieNode* node, string prefix)
    {
        if (node->endOfWord)
        {
            cout << prefix << endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (node->children[i])
            {
                printTrie(node->children[i], prefix + node->children[i]->letter);
            }
        }
    }

    void print()
    {
        printTrie(&root, "");
    }

    // Метод для удаления узла
    bool deleteNode(TrieNode* node, const string& key, int depth = 0)
    {
        if (!node)
        {
            return false;
        }

        if (depth == key.size())
        {
            if (node->endOfWord)
            {
                node->endOfWord = false;
            }

            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (node->children[i])
                {
                    return false;
                }
            }

            return true;
        }

        int index = key[depth] - 'a';
        if (deleteNode(node->children[index], key, depth + 1))
        {
            delete node->children[index];
            node->children[index] = NULL;

            if (!node->endOfWord)
            {
                for (int i = 0; i < ALPHABET_SIZE; i++)
                {
                    if (node->children[i])
                    {
                        return false;
                    }
                }

                return true;
            }
        }

        return false;
    }
};


int main() // Пример из мудла - удаление всех слов с заданной подстрокой
{
    Trie T;
    T.insert("world");
    T.insert("within");
    T.insert("day");
    T.insert("actually");
    T.insert("flat");
    T.insert("war");
    T.insert("warframe");
    T.insert("warlord");
    T.insert("warleader");
    T.insert("warfare");

    T.print();
    cout << endl;

    T.removeWordsWithSubstring("war");

    T.print();
}