#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::set;
using std::map;

vector<vector<int>> to, e;
int n, m;

struct Data {
    vector<int> a; // a[0] : statue, a[1~n] : data
    // origin: 0, final: 1
    int depth;
    int &operator[](int x) { return a[x]; }
    int operator[](int x) const { return a[x]; }
    bool operator<(const Data &b) const { return a < b.a; }
    operator bool() const { return a.size() ? a.front() : -1; }
    Data(int N = n, int d = 0) {
        a.assign(n + 1, 0);
        depth = d;
    }

    Data operator+(int x) const { return {a, depth + x};}

    Data(vector<int> A, int d = 0) { a = A, depth = d; }

    size_t size() const { return a.size(); }

    Data operator+(const Data &b) const {
        Data ans = *this;
        for (int i = 0; i < a.size() && i < b.size(); i++) {
            ans[i] += b[i];
        }
        return ans;
    }

    Data operator+=(const Data &b) { return *this = *this + b; }

    Data operator-(const Data &b) const {
        Data ans = *this;
        for (int i = 0; i < a.size() && i < b.size(); i++) {
            ans[i] -= b[i];
        }
        return ans;
    }

    Data operator-=(const Data &b) { return *this = *this - b; }

    int query() {
        int ans = 0;
        for (int i : a) ans += i;
        return ans - (a.size() ? a.front() : 1);
    }

    Data operator!() const { Data x = *this; x[0] ^= 1; return x;}

    Data operator~() const {
        Data A = *this;
        for (int i = 1; i < a.size(); i++) A[i] = !a[i];
        return A;
    }
};

bool check(Data a) {
    for (int i = 1; i <= n; i++) {
        for (int v: to[i]) {
            if (a[i] && a[v]) return false;
        }
    }
    return true;
}

set<Data> st;
vector<Data> ST;
vector<bool> vis;

void dfs(queue<Data> &q, const Data &f, int k, int i = 1, Data change = n) {
    if (i > n || !k) {
        Data ans = !(f[0] ? f - change : f + change);
        if (check((f[0] ? f : ~f) - change) && st.find(ans) == st.end()) q.push(ans), st.insert(ans);
        return;
    }
    dfs(q, f, k, i + 1, change);
    if (!f[i] ^ f[0]) {
        change[i] = 1;
        dfs(q, f, k - 1, i + 1, change);
    }
}

int bfs(int k) {
    queue<Data> q;
    q.push({});
    st.clear();
    st.insert(n);
    while (!q.empty()) {
        Data f = q.front();
        q.pop();
        f.depth++;
        if ((~f).query() <= k && !f[0]) return f.depth;
        dfs(q, f, k);
    }
    return 0;
}

using it = std::set<Data>::iterator;

int find(Data x) {
    return std::lower_bound(ST.begin(), ST.end(), x) - ST.begin();
}

void dfs(vector<Data> &q, const Data &f, vector<int> &last, int k, int i = 1, Data change = n) {
    if (i > n || !k) {
        Data ans = !(f[0] ? f - change : f + change);
        if (check((f[0] ? f : ~f) - change) &&
            st.find(ans) != st.end() && !vis[find(ans)]) 
                q.push_back(ans), last[find(ans)] = find(f), vis[find(ans)] = true;
        return;
    }
    dfs(q, f, last, k, i + 1, change);
    if (!f[i] ^ f[0]) {
        change[i] = 1;
        dfs(q, f, last, k - 1, i + 1, change);
    }
}

auto getmake(int k) {
    if (!bfs(k)) return ;
    vector<Data> q;
    q.push_back({});
    // st.clear();
    // st.insert(n);
    vector<int> last(st.size());
    vis.assign(st.size(), 0);
    ST.clear();
    for (Data i : st) {
        ST.push_back(i);
    }
    for (int i = 0; i < q.size(); i++) {
        Data f = q[i];
        // q.pop();
        f.depth++;
        if ((~f).query() <= k && !f[0]) {
            vector<int> ans;
            for (int t = find(f); t; t = last[t]) {
                ans.push_back(t);
            }
            for (int j = ans.size() - 1; j >= 0; j--) {
                for (int t : ST[ans[j]].a) {
                    cout << t << " ";
                }
                cout << "\n";
            }
            return;
        }
        dfs(q, f, last, k);
    }
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
    // cout << bfs(2);
    int l = 0, r = n;
    while (l < r) {
        int mid = ((l + r) >> 1);
        if (bfs(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << " " << bfs(l) << "\n";
    getmake(l);
    // cout << bfs(7) << "\n";
    // getmake(7);
}