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

int n, m;
vector<int> wt;
vector<vector<int>> e;
vector<int> dfn, low, col, inst, ws;
int cnt = 0, cc = 0;
stack<int> st;

void tarjan(int u) {
    dfn[u] = ++cnt;
    st.push(u);
    inst[u] = true;
    for (int v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inst[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        cc++;
        while (st.empty()) {
            int s = st.top();
            st.pop();
            col[s] = cc;
            if (s == u) break;
        }
    }
}

void solve() {
    cin >> n >> m;
    assign(n + 1, wt, e, inst, dfn, low, col);

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