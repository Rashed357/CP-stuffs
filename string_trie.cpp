#include <bits/stdc++.h>
using namespace std;

/*
    Trie (Prefix Tree)

    Supports:
    1. insert(word)         -> add a word
    2. countEqual(word)     -> how many times this exact word inserted
    3. countPrefix(prefix)  -> how many words start with this prefix
    4. erase(word)          -> remove one occurrence of word

    Time Complexity:
    All operations: O(length of string)

    Space Complexity:
    O(total characters inserted)
*/

struct Trie {

    struct Node {
        Node* next[26];   // children (a-z)
        int prefix_count; // how many words pass through this node
        int end_count;    // how many words end here

        Node() {
            prefix_count = 0;
            end_count = 0;
            for (int i = 0; i < 26; i++) {
                next[i] = NULL;
            }
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert a word
    void insert(string &s) {
        Node* cur = root;

        for (char c : s) {
            int idx = c - 'a';

            if (cur->next[idx] == NULL) {
                cur->next[idx] = new Node();
            }

            cur = cur->next[idx];
            cur->prefix_count++; // this node is used in prefix
        }

        cur->end_count++; // word ends here
    }

    // Count exact occurrences of a word
    int countEqual(string &s) {
        Node* cur = root;

        for (char c : s) {
            int idx = c - 'a';

            if (cur->next[idx] == NULL) {
                return 0;
            }

            cur = cur->next[idx];
        }

        return cur->end_count;
    }

    // Count how many words start with prefix
    int countPrefix(string &s) {
        Node* cur = root;

        for (char c : s) {
            int idx = c - 'a';

            if (cur->next[idx] == NULL) {
                return 0;
            }

            cur = cur->next[idx];
        }

        return cur->prefix_count;
    }

    // Erase one occurrence of a word
    void erase(string &s) {
        Node* cur = root;

        for (char c : s) {
            int idx = c - 'a';

            if (cur->next[idx] == NULL) {
                return; // word doesn't exist
            }

            cur = cur->next[idx];
            cur->prefix_count--;
        }

        cur->end_count--;
    }

    // Free memory (important in large constraints)
    void clear(Node* cur) {
        for (int i = 0; i < 26; i++) {
            if (cur->next[i]) {
                clear(cur->next[i]);
            }
        }
        delete cur;
    }

    ~Trie() {
        clear(root);
    }
};
