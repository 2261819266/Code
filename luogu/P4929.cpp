#include <bits/stdc++.h>
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
        Node *U, *D, *L, *R;
        Node() { U = D = L = R = this; }
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

        Node *operator[](const int &x) const { return (*this)[FACE[x]];}
        Node *&operator[](const int &x) { return (*this)[FACE[x]];}
    };
    int n, m;
    Node head;
    vector<Node> fst, c;
    DL(int N, int M) : n(N), m(M), head(), fst(n + 1), c(m + 1) {
        head.R = &c[1];
        c[1].L = &head;
        head.L = &c[m];
        c[m].R = &head;
        for (int i = 1; i < m; i++) {
            c[i].R = &c[i + 1];
            c[i + 1].L = &c[i];
        }
    }

    
};

void main() {
    int n, m;
    cin >> n >> m;
    
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}