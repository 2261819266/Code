#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

vector<vector<int>> to, e;
int n, m;

bool dfs(int k, vector<bool> l = vector<bool>(n + 1, 1), vector<bool> r = vector<bool>(n + 1, 0)) {

}

int main() {
    cin >> n >> m;
    to.assign(n + 1, vector<int>());
    e.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
        e[u][v] = e[v][u] = 1;
    }
}