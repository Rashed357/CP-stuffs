#include <bits/stdc++.h>
using namespace std;

/*
    Trie (Prefix Tree)

    Operations:
    1. insert(word)
    2. countEqual(word)
    3. countPrefix(prefix)
    4. contains(word)
    5. startsWith(prefix)
    6. erase(word)
    7. totalWords()

    Time:
        O(length of string) per operation

    Space:
        O(total characters inserted)
*/

struct Trie
{
    struct Node
    {
        Node* next[26];

        int prefix_count;   // how many words pass through this node
        int end_count;      // how many words end here

        Node()
        {
            prefix_count = 0;
            end_count = 0;

            for(int i = 0; i < 26; i++)
                next[i] = NULL;
        }
    };

    Node* root;

    Trie()
    {
        root = new Node();
    }

    // Insert one word
    void insert(const string &s)
    {
        Node* cur = root;

        // root also represents empty prefix
        cur->prefix_count++;

        for(char c : s)
        {
            int idx = c - 'a';

            if(cur->next[idx] == NULL)
                cur->next[idx] = new Node();

            cur = cur->next[idx];
            cur->prefix_count++;
        }

        cur->end_count++;
    }

    // Count exact occurrences
    int countEqual(const string &s)
    {
        Node* cur = root;

        for(char c : s)
        {
            int idx = c - 'a';

            if(cur->next[idx] == NULL)
                return 0;

            cur = cur->next[idx];
        }

        return cur->end_count;
    }

    // Count words having this prefix
    int countPrefix(const string &s)
    {
        Node* cur = root;

        for(char c : s)
        {
            int idx = c - 'a';

            if(cur->next[idx] == NULL)
                return 0;

            cur = cur->next[idx];
        }

        return cur->prefix_count;
    }

    // Exact word exists?
    bool contains(const string &s)
    {
        return countEqual(s) > 0;
    }

    // At least one word starts with this prefix?
    bool startsWith(const string &s)
    {
        return countPrefix(s) > 0;
    }

    // Erase one occurrence
    void erase(const string &s)
    {
        Node* cur = root;
        vector<Node*> path;

        path.push_back(root);

        // First check whether the full word exists
        for(char c : s)
        {
            int idx = c - 'a';

            if(cur->next[idx] == NULL)
                return;

            cur = cur->next[idx];
            path.push_back(cur);
        }

        // Exact word was never inserted
        if(cur->end_count == 0)
            return;

        // Decrease prefix counts
        for(Node* node : path)
            node->prefix_count--;

        // Remove one occurrence
        cur->end_count--;
    }

    // Total number of inserted words
    int totalWords()
    {
        return root->prefix_count;
    }

    // Free memory
    void clear(Node* cur)
    {
        for(int i = 0; i < 26; i++)
        {
            if(cur->next[i] != NULL)
                clear(cur->next[i]);
        }

        delete cur;
    }

    ~Trie()
    {
        clear(root);
    }
};


int main()
{
    Trie trie;

    // Insert words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apple");
    trie.insert("application");
    trie.insert("bat");

    // Exact count
    cout << trie.countEqual("apple") << endl;
    // 2

    cout << trie.countEqual("app") << endl;
    // 1

    cout << trie.countEqual("banana") << endl;
    // 0

    // Prefix count
    cout << trie.countPrefix("app") << endl;
    // 4
    // apple, apple, app, application

    cout << trie.countPrefix("ap") << endl;
    // 4

    cout << trie.countPrefix("bat") << endl;
    // 1

    // Contains
    cout << trie.contains("apple") << endl;
    // 1

    cout << trie.contains("banana") << endl;
    // 0

    // Starts with
    cout << trie.startsWith("app") << endl;
    // 1

    cout << trie.startsWith("xyz") << endl;
    // 0

    // Total words
    cout << trie.totalWords() << endl;
    // 5

    // Empty prefix = all words
    cout << trie.countPrefix("") << endl;
    // 5

    // Erase one "apple"
    trie.erase("apple");

    cout << trie.countEqual("apple") << endl;
    // 1

    cout << trie.countPrefix("app") << endl;
    // 3

    cout << trie.totalWords() << endl;
    // 4

    // Try erasing a word that doesn't exist
    trie.erase("hello");

    // Try erasing "app"
    trie.erase("app");

    cout << trie.countEqual("app") << endl;
    // 0

    cout << trie.startsWith("app") << endl;
    // 1
    // application still exists

    return 0;
}
