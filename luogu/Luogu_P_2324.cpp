#include <algorithm>
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

void solve() {
    string s;
    vector<vector<int>> a(5);
    int X, Y;
    for (int i = 0; i < 5; i++) {
        cin >> s;
        for (char c : s) {
            a[i].push_back(c == '*' ? -1 : (c == '1'));
            if (a[i].back() == -1) X = i, Y = a[i].size() - 1;
        }
    }

    auto check = [](int x, int y) -> bool {
        return x >= 0 && y >= 0 && x < 5 && y < 5;
    };

    const int value[5][5] = {
        {1, 1, 1, 1, 1}, 
        {0, 1, 1, 1, 1},
        {0, 0, -1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    auto get_value = [&]() -> int {
        int ans = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                ans += a[i][j] != value[i][j];
            }
        }
        return ans;
    };

    const int fac[8][2] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
    int ans = 16;

    auto dfs = [&](auto &&self, int x, int y, int step = 0) -> int {
        if (get_value() == 0) return step;
        for (auto fc : fac) {
            int fx = x + fc[0], fy = y + fc[1];
            if (!check(fx, fy)) continue;
            swap(a[x][y], a[fx][fy]);
            if (get_value() + step <= ans) {
                int ret = self(self, fx, fy, step + 1);
                if (ret < ans) ans = ret;
            }
            swap(a[x][y], a[fx][fy]);
        }
        return ans;
    };
    dfs(dfs, X, Y);
    if (ans > 15) ans = -1;
    cout << ans << endl;
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}