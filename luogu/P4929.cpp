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

using v1 = vector<int>;
using v2 = vector<v1>;

void main() {
    int n, m;
    cin >> n >> m;
    v2 a(n + 1, v1(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    auto remove = [&](int x) -> bool {
        a[x][0] = x;
        bool k = false;
        for (int i = 1; i <= m; i++) {
            if (a[x][i] && !a[0][i]) {
                a[0][i] = -x;
                for (int j = 1; j <= n; j++) {
                    if (a[j][i] && !a[j][0]) a[j][0] = -x;
                }
            }
            if (!a[x][i] && !a[0][i]) k = true;
        }
        return !k;
    };

    auto recover = [&](int x) {
        for (int i = 1; i <= n; i++) if (abs(a[i][0]) == x) a[i][0] = 0;
        for (int i = 1; i <= m; i++) if (abs(a[0][i]) == x) a[0][i] = 0;
    };

    auto check = [&](const v1 &ans) {
        v1 res(m + 1, 0);
        for (int i : ans) {
            res += a[i];
        }
        for (int i = 1; i <= m; i++) {
            if (res[i] > 1) return -1;
            if (res[i] == 0) return 0;
        }
        return 1;
    };

    auto dfs = [&](auto &&self, int x = 1) -> bool {
        for (int i = x; i <= n; i++) {
            if (!a[i][0]) {
                bool k = remove(i);
                bool K1 = true, K2 = true;
                for (int j = 1; j <= n; j++) K1 &= (bool)a[j][0];
                for (int j = 1; j <= m; j++) K2 &= (bool)a[0][j];
                if (!K1 && !K2) self(self, i + 1);
                else {
                    if (k) {
                        vector<int> ans;
                        for (int j = 1; j <= n; j++) {
                            for (int l = 1; l <= n; l++) {
                                if (j == a[l][0]) {
                                    cout << j << spc;
                                    ans.push_back(j);
                                    // cerr << check(ans) << endl;
                                    break;
                                }
                            }
                        }
                        cout << endl;
                        // for (int j : ans) cout << a[j] << endl;
                        exit(0);
                    }
                }
                recover(i);
            }
        }
        return true;
    };

    dfs(dfs);
    cout << "No Solution!";
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}