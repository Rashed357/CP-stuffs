#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        Node* child[2];
        int cnt;

        Node() {
            child[0] = child[1] = NULL;
            cnt = 0;
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert a number
    void insert(int num) {
        Node* cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            if (!cur->child[bit])
                cur->child[bit] = new Node();

            cur = cur->child[bit];
            cur->cnt++;
        }
    }

    // Remove a number
    void erase(int num) {
        Node* cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            cur = cur->child[bit];
            cur->cnt--;
        }
    }

    // Maximum XOR with given number
    int maxXor(int num) {
        Node* cur = root;
        int ans = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            if (cur->child[1 - bit] && cur->child[1 - bit]->cnt > 0) {
                ans |= (1 << i);
                cur = cur->child[1 - bit];
            } else {
                cur = cur->child[bit];
            }
        }
        return ans;
    }

    // Minimum XOR with given number
    int minXor(int num) {
        Node* cur = root;
        int ans = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            if (cur->child[bit] && cur->child[bit]->cnt > 0) {
                cur = cur->child[bit];
            } else {
                ans |= (1 << i);
                cur = cur->child[1 - bit];
            }
        }
        return ans;
    }

    // Count how many numbers already inserted
    int size() {
        return root->cnt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Trie t;

    // Example usage
    t.insert(5);
    t.insert(10);

    cout << "Max XOR with 3 = " << t.maxXor(3) << '\n';
    cout << "Min XOR with 3 = " << t.minXor(3) << '\n';

    return 0;
}
