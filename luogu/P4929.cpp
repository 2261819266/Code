#include <bits/stdc++.h>
#include <memory>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P4929
#define fop fo(P4929)

using namespace std;

namespace Problem {
template <typename t>
ostream &operator<<(ostream &out, const vector<t> &A) {
    for (const t &i : A) out << i << spc;
    return out;
}

template <typename t>
void print(const t &x, int l = 0, int r = 0) {
    cout << x << spc;
}

template <typename t>
void print(const vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    print(A[i], l, r);
    }
    cout << endl;
}

template <typename t>
istream &operator>>(istream &in, vector<t> &A) {
    for (t &i : A) in >> i;
    return in;
}

template<typename t>
void scan(t &x, int l = 0, int r = 0) {
    cin >> x;
}

template<typename t>
void scan(vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    scan(A[i], l, r);
    }
}

template<typename it>
void assign(vector<int> &a, it p) {
    a.assign(*p, 0);
}

template<typename T, typename it>
void assign(vector<T> &a, it p) {
    T t;
    assign(t, p + 1);
    a.assign(*p, t);
}

template<typename T>
void assign(vector<T> &a, const vector<int> &p) {
    assign(a, p.begin());
}

using PII = pair<int, int>;

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

ostream &operator<<(ostream &out, const PII &a) {
    return out << a.first << spc << a.second << spc;
}

template<typename T> vector<T> operator+(const vector<T> &A, const vector<T> &B) {
    int n = A.size(), m = B.size(), k = max(m, n);
    vector<T> C(k, 0);
    for (int i = 0; i < k; i++) {
        if (i < n) C[i] += A[i];
        if (i < m) C[i] += B[i];
    }
    return C;
}

template<typename T> vector<T> operator+=(vector<T> &A, const vector<T> &B) { return A = A + B; }

const char FACE[5] = "UDLR";

struct DL {
    struct Node {
        int x, y;
        Node *U, *D, *L, *R;
        Node(int i = 0, int j = 0) : x(i), y(j) { U = D = L = R = this; }
        Node *&operator[](const char &c) {
            if (c == 'U') return U;
            if (c == 'D') return D;
            if (c == 'L') return L;
            return R;
        }
        Node *operator[](const char &c) const {
            if (c == 'U') return U;
            if (c == 'D') return D;
            if (c == 'L') return L;
            if (c == 'R') return R;
            return nullptr;
        }

        Node *operator[](const int &X) const { return (*this)[FACE[X]];}
        Node *&operator[](const int &X) { return (*this)[FACE[X]];}
    };
    int n, m;
    Node *head;
    vector<Node*> f;
    vector<Node*> c;
    DL(int N, int M) : n(N), m(M), head(new Node()), f(n + 1, 0), c(m + 1, 0) {
        for (int i = 1; i <= m; i++) c[i] = new Node();
        head->R = c[1];
        c[1]->L = head;
        head->L = c[m];
        c[m]->R = head;
        for (int i = 1; i < m; i++) {
            c[i]->R = c[i + 1];
            c[i + 1]->L = c[i];
        }
    }

    void insert(int x, int y) {
        Node *nd = new Node(x, y);
        if (!f[x]) f[x] = nd;
        else {
            nd->L = f[x]->L;
            nd->R = f[x];
            f[x]->L = f[x]->L->R = nd;
        }
        nd->U = c[y]->U;
        c[y]->U = c[y]->U->D = nd;
        nd->D = c[y];
    }

    void remove(Node *p) {
        p->D->U = p->U;
        p->U->D = p->D;
        p->L->R = p->R;
        p->R->L = p->L;
    }

    void recover(Node *p) {
        p->D->U = p;
        p->U->D = p;
        p->L->R = p;
        p->R->L = p;
    }

    void dance(stack<int> &s = *(new stack<int>())) {
        if (head->R == head) {
            while (!s.empty()) {
                cout << s.top() << spc;
            }
            exit(0);
        } 
        if (head->R->D == head->R) return;
        Node *p = head->R;
        for (Node *q = p->D; q != p; q = q->D) {
            stack<Node*> st;
            vector<int> vis(n + 1, 0);
            for (Node *i = q; i &&i != i->R; i = i->R) {
                for (Node *j = i; j != j->U; j = j->U) {
                    if (!j->x) {
                        remove(j);
                        st.push(j);
                        continue;
                    }
                    // if (vis[j->x]) continue;
                    vis[j->x] = true;
                    remove(j);
                    st.push(j);
                    // for (Node *k = j->R; k != k->R; k = k->R) {
                    //     remove(k);
                    //     st.push(k);
                    //     // if (k == k->R) k->R = k->L = 0;
                    // }
                    // remove(j);
                    // st.push(j);
                }
            }
            for (int i = 1; i <= n; i++) if (vis[i]) {
                for (Node *j = f[i]->R; j !=j->R; j = j->R) {
                    remove(j);
                    st.push(j);
                }
                remove(f[i]);
                st.push(f[i]);
            }
            s.push(q->x);
            dance(s);
            s.pop();
            while (!st.empty()) {
                recover(st.top());
                st.pop();
            }
        }
    }
};

void main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> A(n + 1, vector<int>(m + 1));
    DL a(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
            if (A[i][j]) a.insert(i, j);
        }
    }
    a.dance();
    cout << "No Solution!\n";
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}