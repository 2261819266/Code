#include <bits/stdc++.h>
#include <functional>
#include <unordered_map>
#include <vector>
#define int long long
#define Problem P1630
#define endl "\n"
#define space " "

using namespace std;


namespace Problem {
#define max(x, y) ((x) < (y) ? (y) : (x))
template<typename t>
istream &operator>>(istream &in, vector<t> &a) {
    for (t &i : a) in >> i;
    return in;
}

template<typename t>
ostream &operator<<(ostream &out, const vector<t> &a) {
    for (const t &i : a) out << i;
    return out;
}

const int M = 1e4;

int pow(int x, int y) {
    if (y == 0) return 1;
    return pow(x * x % M, y / 2) * (y % 2 ? x : 1) % M; 
}

void solve() {
    int a, b;
    cin >> a >> b;
    int s = 0, ans = 0;
    for (int i = 1; i <= M; i++) {
        (s += pow(i, b)) %= M;
    }
    ans = a / M * s % M;
    for (int i = 1; i <= a % M; i++) {
        (ans += pow(i, b)) %= M;
    }
    cout << ans << endl;
}

void main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
}


signed main() {
    Problem::main();
    return 0;
}
