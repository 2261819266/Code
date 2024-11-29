#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

template<typename T>
void assign(int n, vector<T> &x) {
    x.assign(n, T());
}

template<typename T, typename ...Args>
void assign(int n, vector<T> &x, vector<Args> &...y) {
    assign(n, x);
    assign(n, y...);
}

inline void init() {
    return;
}

using value_t = double;
using Point = vector<value_t>;
using v1 = Point;
using v2 = vector<v1>;

struct Matrix {
    int n;
    v2 a;
    Matrix(int N) : n(N), a(n, v1(n + 1)) {}
    friend istream &operator>>(istream &in, Matrix &x) {
        for (auto &i : x.a) for (auto &j : i) in >> j;
        return in;
    }

    v1 gauss() {
        v1 ans;
        for (int i = 0; i < n; i++) {
            int t = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[t][i])) t = j;
            }
            swap(a[t], a[i]);
            for (int j = n; j >= i; j--) a[i][j] /= a[i][i];
            for (int j = 0; j < n; j++) if (i != j) {
                for (int k = n; k >= i; k--) {
                    a[j][k] -= a[j][i] * a[i][k];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            ans.push_back(a[i][n]);
        }
        return ans;
    }
} ;

void solve() {
    int n;
    cin >> n;
    v2 x(n + 1, v1(n));
    for (auto &i : x) for (auto &j : i) cin >> j;
    Matrix a(n + 1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            a.a[i][j] = x[i][j];
            a.a[i][n + 1] -= x[i][j] * x[i][j];
        }
        a.a[i][n] = 1;
    }
    auto ans = a.gauss();
    ans.pop_back();
    cout << fixed << setprecision(3);
    for (auto i : ans) cout << -i / 2 << " ";
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}