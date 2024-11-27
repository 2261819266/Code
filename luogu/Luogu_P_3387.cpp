#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

template<typename T>
void assign(int n, T &x) {
    x.assign(n, {});
}

template<typename T, typename ...Args>
void assign(int n, T &x, Args &...y) {
    assign(n, x);
    assign(n, y...);
}

inline void init() {
    return;
}

vector<int> dfn, low;
vector<vector<int>> e, e2;

void solve() {
    int n, m;
    cin >>> n >> m;
    
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