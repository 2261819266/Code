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

    vector<int> operator[](int x) const {
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

    bool operator==(const Matrix &b) const {
        return a == b.a;
    }
};

bool solve() {
    int n, m;
    cin >> m >> n;
    Matrix a(n, m), b(n, m), c(n, m);
    cin >> a >> b >> c;
    return a * b == c;
}

const char OUTPUT[2][4] = {"No", "Yes"};

signed main() {
    fo(matrix)
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cout << OUTPUT[solve()] << "\n";
    }
}