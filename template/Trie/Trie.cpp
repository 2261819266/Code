#ifndef __TRIE__
#define __TRIE__

#include <unordered_map>


class Trie {
  private:

    struct Node {
        std::unordered_map<char, Node*> a;
        int sum;

        Node() : sum(0), a() {}
        ~Node() { for (const auto &i : a) delete i.second; }

        Node* &operator[](char x) { return a[x]; }
    };

    Node *root;
  public:
    Trie() : root(new Node()) {}
    ~Trie() { delete root; }

    void insert(const char *s) {
        Node *p = root;
        while (*s) {
            if (!(*p)[*s]) (*p)[*s] = new Node();
            p = (*p)[*s];
            p->sum++;
            s++;
        }
    }

    int query(const char *s) const {
        Node *p = root;
        while (*s) {
            if (!(*p)[*s]) return 0;
            p = (*p)[*s];
            s++;
        }
        return p->sum;
    };
};

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e6 + 9;
char s[maxn];

void solve() {
    int n, m;
    cin >> n >> m;
    Trie a;
    while (n--) {
        cin >> s;
        a.insert(s);
    }
    while (m--) {
        cin >> s;
        cout << a.query(s) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}



#endif