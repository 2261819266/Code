#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using std::cin;
using std::cout;
using std::set;
using std::vector;
using PII = std::pair<int, int>;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    set<PII> e;
    vector<int> deg(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        e.insert({u, v});
        e.insert({v, u});
        deg[u]++, deg[v]++;
    }
    int cnt = 0;
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (deg[i] >= 3) {
            ++cnt;
            vis[i] = 1;
            deg[i] = 0;
            for (int j = 1; j <= n; ++j) {
                if (e.find({i, j}) != e.end()) {
                    e.erase({i, j});
                    e.erase({j, i});
                    deg[j]--;
                }
            }
        }
    }
    vector<vector<int>> e1(n + 1);
    vector<int> block(n + 1, 1);
    for (auto [u, v] : e) {
        e1[u].push_back(v);
        e1[v].push_back(u);
    }
    int maxt = 0;
    int ans = 0;
    int cnt1 = 0;
    int flag1 = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cnt1++;
            bool flag = false;
            auto dfs = [&](auto &&dfs, int u) -> void {
                for (auto v : e1[u]) {
                    if (vis[v]) {
                        continue;
                    }
                    if (deg[v] == 1) {
                        flag = true;
                    }
                    vis[v] = 1;
                    block[cnt1]++;
                    // std::cerr << u << " " << v << " " << block[cnt1] << "\n";
                    dfs(dfs, v);
                }
            };
            vis[i] = 1;
            dfs(dfs, i);
            if (block[cnt1] == 1) {
                ans += 2;
                flag1 = 1;
                continue;
            }
            if (flag) {
                maxt += block[cnt1] / 2;
            } else {
                maxt += block[cnt1] / 2 + block[cnt1] % 2;
            }
            // std::cerr << block[cnt1] << "\n";
            if (block[cnt1] % 2 == 0) {
                ans += 4;
            } else {
                ans += 8;
            }
        }
    }
    ans--;
    // std::cerr << cnt << " " << maxt;
    cout << cnt + std::max(maxt, flag1) << " " << ans << std::endl;
    return 0;
}