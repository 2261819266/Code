#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
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

struct Matrix {
    int n;
    vector<vector<value_t>> a;
    Matrix(int N) : n(N), a(n, vector<value_t>(n + 1)) {}
    friend istream &operator>>(istream &in, Matrix &x) {
        for (auto &i : x.a) for (auto &j : i) in >> j;
        return in;
    } 

    bool equal(value_t x, value_t y) { return abs(x - y) < 1e-9; }

    int gauss() {
        for (int i = 0; i < n; i++) {
            int t = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[t][i])) t = j;
            }
            swap(a[i], a[t]);
            if (equal(a[i][i], 0)) return false;
            for (int j = n; j >= i; j--) a[i][j] /= a[i][i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = n; k >= i; k--) {
                        a[j][k] -= a[i][k] * a[j][i];
                    }
                }
            }
        }
        return true;
    }
};

void solve() {
    int n;
    cin >> n;
    Matrix x(n);
    cin >> x;
    int f = x.gauss();
    if (!f) {
        cout << "No Solution" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(2) << x.a[i][n] / x.a[i][i] << endl;
        }
    }
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