#include <iostream>
#include <vector>
#include <string>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;
using std::vector;

const int maxl = 22;

vector<int> operator+(const vector<int> &a, const vector<int> &b) {
    vector<int> ans = a;
    for (int i = 0; i < a.size() && i < b.size(); i++) {
        ans[i] |= b[i];
    }
    return ans;
}

vector<int> operator+=(vector<int> &a, const vector<int> &b) { return a = a + b; }

int query(const vector<int> &a) {
    int ans = 0;
    for (int i : a) {
        ans += (bool)i;
    }
    return ans;
}

int operator+(int a, const vector<int> &b) { return a + query(b); }

int operator+=(int &a, const vector<int> &b) { return a = a + b; }

int solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    vector<vector<int>> I;
    for (string &s : a) {
        cin >> s;
        vector<int> J(10, 0);
        for (int j : s) {
            J[j - '0'] |= 1;
        }
        I.push_back(J);
    }
    vector<vector<int>> s(n, vector<int>(n, 0)), f(n, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++) {
        vector<int> J = I[i];
        s[i][i] += J;
        for (int j = i + 1; j < n; j++) {
            J += I[j];
            s[i][j] += J;
        }
        f[i][1] = s[0][i];
    }
    for (int i = 1; i < n; i++) {
        int J = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (s[j + 1][i] > J) {
                J = s[j + 1][i];
                for (int k = 2; k <= min(m, i + 1); k++) {
                    f[i][k] = max(f[i][k], f[j][k - 1] + J);
                }
            }
            if (J == 10) break;
        }
        // for (int k = 2; k <= min(m, i + 1); k++) {
        //     int ans = 0;
        //     for (int j = i - 1; j >= 0; j--) {
        //         ans = max(ans, f[j][k - 1] + s[j + 1][i]);
        //         // if (s[j + 1][i] == 10 || ans - f[j][k - 1] > 10)
        //         //     break;
        //     }
        //     f[i][k] = ans;
        // }
    }

    // for (vector<int> i : f) {
    //     for (int j : i) cout << j << " ";
    //     cout << "\n";
    // }

    return f[n - 1][m];
}

int main() {
    // fo(partition)
    int T;
    cin >> T;
    while (T--) {
        cout << solve() << "\n";
    }
}
