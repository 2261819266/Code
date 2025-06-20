#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

struct Task {
    int I, len;
    vector<int> a;  
    int &operator[](int x) { return x < a.size() ? a[x] : a.back(); }
    void push_back(int x) { return a.push_back(x); } 
};

vector<vector<int>> e;
vector<Task> a;
vector<int> f;

void addEdge(int u, int v) {
    e[u].push_back(v);
}

int dfs(int u) {
    if (f[u]) return f[u];
    int ans = 0;
    for (int i : e[u]) {
        ans = max(ans, dfs(i));
    }
    return f[u] = ans + a[u].len;
}

int main() {
    int n;
    cin >> n;
    a.assign(n + 1, {});
    f.assign(n + 1, 0);
    e.assign(n + 1, {});
    for (int i = 1; i <= n; i++) {
        cin >> a[i].I >> a[i].len;
        int x;
        do {
            cin >> x;
            a[i].push_back(x);
            addEdge(x, i);
        } while (x);
    }
    cout << dfs(1);
}