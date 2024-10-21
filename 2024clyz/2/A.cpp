#include <iostream>
#include <istream>
#include <vector>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;
using std::istream;
#define int long long

struct Matrix {
    vector<vector<int>> a;
    int M;
    Matrix(int n, int m) {
        a.assign(n, vector<int>(n, 0));
        M = m;
    }

    friend istream &operator>>(istream &in, Matrix &mat) {
        for (vector<int> &i : mat.a) {
            for (int &j : i) in >> j, j %= mat.M;
        }
        return in;
    }

    vector<int> &operator[](int x) {
        return a[x];
    }

    const vector<int> &operator[](int x) const {
        return a[x];
    }

    Matrix operator*(const Matrix &b) const {
        int n = a.size();
        Matrix ans(n, M);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans[i][j] += a[i][k] * b[k][j]) %= M;
                }
            }
        }
        return ans;
    }

    vector<int> operator*(const vector<int> &b) const {
        int n = a.size();
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                (ans[i] += a[i][j] * b[j]) %= M;
            }
        }
        return ans;
    }

    bool operator==(const Matrix &b) const {
        return a == b.a;
    }
};

vector<int> get_random_vector(int n, int m) {
    vector<int> a(n, 0);
    for (int &i : a) i = rand() % m;
    return a;
}

bool solve() {
    int n, m;
    cin >> m >> n;
    Matrix a(n, m), b(n, m), c(n, m);
    cin >> a >> b >> c;
    bool ans = true;
    int k = 6;
    while (k--) {
        vector<int> r = get_random_vector(n, m);
        ans &= a * (b * r) == c * r;
    }
    return ans;
}

const char OUTPUT[2][4] = {"No", "Yes"};

signed main() {
#ifndef LOCAL
    fo(matrix)
#endif
    srand(time(0));
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cout << OUTPUT[solve()] << "\n";
    }
}