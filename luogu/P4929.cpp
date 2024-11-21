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

struct de_Link {
    int n;
    vector<int> a, b;
    int st, ed;
    de_Link(int N) : n(N), a(n + 2), b(n + 2), st(0), ed(N + 1) {
        for (int i = 0; i <= n + 1; i++) {
            a[i] = i + 1;
            b[i] = i - 1;
        }
    }

    operator vector<int>() const {
        vector<int> ans;
        for (int i = a[st]; i != ed; i = a[i]) {
            ans.push_back(i);
        }
        return ans;
    }

    de_Link &operator-=(int x) {
        a[b[x]] = a[x];
        b[a[x]] = b[x];
        return *this;
    }

    de_Link &operator+=(PII X) {
        int x = X.first, y = X.second, z = a[x];
        a[x] = y, b[z] = y;
        a[y] = z, b[y] = x;
        return *this;
    }

    de_Link &operator+=(int x) {
        for (int i = st; i != ed; i = a[i]) {
            if (a[i] > x) return *this += {i, x};
        }
        return *this;
    }

    bool empty() { return a[st] == ed;}
};

void main() {
    int n, m;
    cin >> n >> m;
    v2 a(n + 1, v1(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    // auto remove = [&](int x) -> bool {
    //     a[x][0] = x;
    //     bool k = false;
    //     for (int i = 1; i <= m; i++) {
    //         if (a[x][i] && !a[0][i]) {
    //             a[0][i] = -x;
    //             for (int j = 1; j <= n; j++) {
    //                 if (a[j][i] && !a[j][0]) a[j][0] = -x;
    //             }
    //         }
    //         if (!a[x][i] && !a[0][i]) k = true;
    //     }
    //     return !k;
    // };

    // auto recover = [&](int x) {
    //     for (int i = 1; i <= n; i++) if (abs(a[i][0]) == x) a[i][0] = 0;
    //     for (int i = 1; i <= m; i++) if (abs(a[0][i]) == x) a[0][i] = 0;
    // };

    // auto check = [&](const v1 &ans) {
    //     v1 res(m + 1, 0);
    //     for (int i : ans) {
    //         res += a[i];
    //     }
    //     for (int i = 1; i <= m; i++) {
    //         if (res[i] > 1) return -1;
    //         if (res[i] == 0) return 0;
    //     }
    //     return 1;
    // };
    
    // vector<int> U(n + 1, 0), D(n + 1, 0), L(m + 1, 0), R(m + 1, 0);

    // // init UDLR
    // for (int i = 1; i <= n; i++) {
    //     U[i] = i - 1;
    //     D[i] = (i + 1) % (n + 1);
    // }
    // for (int i = 1; i <= m; i++) {
    //     L[i] = i - 1;
    //     R[i] = (i + 1) % (m + 1);
    // }
    // D[0] = R[0] = 1;
    // U[0] = n;
    // L[0] = m;

    // auto removeX = [&](int X) {
    //     U[D[X]] = U[X];
    //     D[U[X]] = D[X];
    // };

    // auto removeY = [&](int Y) {
    //     L[R[Y]] = L[Y];
    //     R[L[Y]] = R[Y];
    // };

    de_Link X(n), Y(m);

    auto remove = [&](int x) {
        bool k = false;
        X -= x;
        a[x][0] = x;
        for (int i : vector<int>(Y)) {
            if (!a[x][i]) {
                k = true;
                continue;
            }
            Y -= i;
            a[0][i] = -x;
            for (int j : vector<int>(X)) {
                if (a[j][i]) X -= j, a[j][0] = -x;
            }
        }
        return !k;
    };

    auto recover = [&](int x) {
        for (int i = 1; i <= n; i++) if (abs(a[i][0]) == x) X += i, a[i][0] = 0;
        for (int i = 1; i <= m; i++) if (abs(a[0][i]) == x) Y += i, a[0][i] = 0;
    };

    auto dfs = [&](auto &&self, int x = 1) -> bool {
        for (int i : vector<int>(X)) {
            bool k = remove(i);
            if (!X.empty() && !Y.empty()) self(self, i + 1);
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