// Реализация Максимки Первицкого

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// узел
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

// Trie-дерево
class Trie {
private:
    TrieNode* root;

    // –екурсивна€ функци€ дл€ проверки слова на симметричность
    bool isSymmetricUtil(const string& word) {
        int start = 0;
        int end = word.length() - 1;
        while (start < end) {
            if (word[start] != word[end])
                return false;
            start++;
            end--;
        }
        return true;
    }

    // –екурсивна€ функци€ дл€ удалени€ симметричных слов
    void removeSymmetricUtil(TrieNode* node, const string& word, string prefix = "") {
        if (node->isEndOfWord && isSymmetricUtil(prefix))
            node->isEndOfWord = false;

        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                char ch = 'a' + i;
                removeSymmetricUtil(node->children[i], word, prefix + ch);
            }
        }
    }

    // –екурсивна€ функци€ дл€ вывода всех слов
    void printWordsUtil(TrieNode* node, string prefix) {
        if (node == nullptr)
            return;

        if (node->isEndOfWord) {
            cout << prefix << endl;
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                char ch = 'a' + i;
                printWordsUtil(node->children[i], prefix + ch);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // ¬ставка слова
    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    void removeSymmetric() {
        removeSymmetricUtil(root, "");
    }

    void printWords() {
        printWordsUtil(root, "");
    }
void removeSub(string str){
    removeSubstring(root,"",str);
    }
    void removeSubstring(TrieNode *node,string prefix,string str){
        if (node == nullptr)
            return;

        if (node->isEndOfWord) {
            if (prefix.find(str)!=std::string::npos) {
                node->isEndOfWord=false;
                cout << prefix << endl;
            }
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                char ch = 'a' + i;
                removeSubstring(node->children[i], prefix + ch,str);
            }
        }
        }
};

int main() {
    Trie trie;

    trie.insert("radar");
    trie.insert("level");
    trie.insert("apple");
    trie.insert("eye");
    trie.insert("hello");
    trie.insert("eyes");
    trie.printWords();
    cout << '\n';
trie.removeSub("le");
    cout << '\n';
trie.printWords();
    return 0;
}
