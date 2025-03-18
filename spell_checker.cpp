#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ALPHABET_SIZE 26

// Trie Node Structure
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

// Trie Class for Spell Checker
class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    // Recursive function to collect suggestions
    void collectSuggestions(TrieNode* node, string currentWord, vector<string>& suggestions) {
        if (node->isEndOfWord)
            suggestions.push_back(currentWord);

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                char nextChar = 'a' + i;
                collectSuggestions(node->children[i], currentWord + nextChar, suggestions);
            }
        }
    }

    // Get word suggestions for a given prefix
    vector<string> getSuggestions(const string& prefix) {
        vector<string> suggestions;
        TrieNode* node = root;

        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index])
                return suggestions;  // No suggestions if prefix not found
            node = node->children[index];
        }

        collectSuggestions(node, prefix, suggestions);
        return suggestions;
    }
};

// Driver Code
int main() {
    Trie trie;
    vector<string> dictionary = {"apple", "app", "apex", "banana", "bat", "ball", "balloon", "cat", "car", "cap"};

    // Insert words into Trie
    for (const string& word : dictionary)
        trie.insert(word);

    string query;
    cout << "Enter a word to check spelling: ";
    cin >> query;

    if (trie.search(query)) {
        cout << query << " is spelled correctly!" << endl;
    } else {
        cout << query << " is not found! Did you mean:" << endl;
        vector<string> suggestions = trie.getSuggestions(query);
        if (suggestions.empty()) {
            cout << "No suggestions available!" << endl;
        } else {
            for (const string& suggestion : suggestions)
                cout << "- " << suggestion << endl;
        }
    }

    return 0;
}
