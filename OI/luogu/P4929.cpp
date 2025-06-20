#include <bits/stdc++.h>
#include <memory>
#include <stack>
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
    vector<vector<int>> A;

struct DL {
    int n, m, cnt;
    static const int maxn = 1e5 + 10;
    int U[maxn] = {}, D[maxn] = {}, L[maxn] = {}, R[maxn] = {}, f[maxn] = {}, size[maxn] = {}, col[maxn] = {}, row[maxn] = {};

    void build(int N, int M) {
        n = N, m = M;
        for (int i = 0; i <= M; i++) {
            L[i] = i - 1;
            R[i] = i + 1;
            U[i] = D[i] = i;
            col[i] = i;
        }
        L[0] = M;
        R[M] = 0;
        cnt = m + 1;
    }

    void insert(int r, int c) {
        col[cnt] = c;
        row[cnt] = r;
        size[c]++;
        U[cnt] = U[c], D[cnt] = c;
        U[c] = D[U[c]] = cnt;
        if (!f[r]) {
            f[r] = cnt;
            L[cnt] = R[cnt] = cnt;
        } else {
            L[cnt] = L[f[r]], R[cnt] = f[r];
            L[f[r]] = R[L[f[r]]] = cnt;
        }
        cnt++;
    }

    bool remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        // if (c == D[c]) return true;
        for (int i = D[c]; i != c; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j], D[U[j]] = D[j], size[col[j]]--;
            }
        }
        return false;
    } 

    void recover(int c) {
        for (int i = U[c]; i != c; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = D[U[j]] = j, size[col[j]]++;
            }
        }
        L[R[c]] = R[L[c]] = c;
    }

    void dance(stack<int> &s = *(new stack<int>())) {
        if (!R[0]) {
            // vector<int> vis(m + 1, 0);
            while (!s.empty()) {
                // vis += A[s.top()];
                cout << s.top() << spc;
                s.pop();
            }
            exit(0);
        }
        int c = R[0];
        for (int i = R[0]; i; i = R[i]) if (size[i] < size[c]) c = i;
        if (remove(c)) return;
        for (int i = D[c]; i != c; i = D[i]) {
            s.push(row[i]);
            for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
            // print();
            dance(s);
            for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
            s.pop();
        }
        recover(c);
    }

    void print() {
        for (int i = 0; i <= cnt; i++) {
            cout << U[i] << spc << D[i] << spc << L[i] << spc << R[i] << endl;
        }
    }
} a;

void main() {
    int n, m;
    cin >> n >> m;
    a.build(n, m);
    A.assign(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
            if (A[i][j]) a.insert(i, j);
        }
    }
    // a.print();
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