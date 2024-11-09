#include <bits/stdc++.h>
#include <vector>
#define int long long
#define Problem P1126
#define endl "\n"
#define space " "
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

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

const char print[3][10] = {"Alice", "Bob", "wow"};

void main() {
    int n;
    cin >> n;
    vector<int> A(n), a[2];
    cin >> A;
    sort(A.begin(), A.end(), [](int x, int y) { return x > y; });
    for (int i : A) {
        a[i % 2].push_back(i);
    }
    int x = min(a[0].size(), a[1].size());
    int y = max(a[0].size(), a[1].size());
    int ans = 0;
    for (int i = 0; i < x; i++) {
        ans += a[0][i] - a[1][i];
    }
    int p = a[0].size() > a[1].size() ? 0 : 1;
    int f = 1;
    for (int i = x; i < y; i++) {
        ans += f * (a[p][i]) * (a[p][i] % 2 == (f == -1));
        f = -f;
        // p ^= 1;
    }

    cout << print[ans > 0 ? 0 : ans < 0 ? 1 : 2] << endl;;
}
}


signed main() {
#ifndef LOCAL
    fo(candy)
#endif
    Problem::main();
    return 0;
}
