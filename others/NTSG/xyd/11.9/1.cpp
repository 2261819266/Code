#include <bits/stdc++.h>
#include <vector>
#define int long long
#define Problem candy
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
    vector<int> a(n);
    cin >> a;
    sort(a.begin(), a.end(), [](int x, int y) { return x > y; });
    int ans = 0, f = 1;
    for (int i : a) {
        ans += i * f * (i % 2 == (f == -1));
        f = -f;
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
