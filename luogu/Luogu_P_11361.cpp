// 2024.11.30 20:22 回忆代码

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

int n;
string s[2], t[2];

int solveA() {
    int ans = 0;
    for (int i = 0; i < n; i++) ans += s[0][i] == s[1][i];
    return ans;
}

int solveB() {
    vector<int> p(1, -1);
    for (int i = 0; i < n; i++) {
        if (t[0][i] == 48) p.push_back(i);
    }
    p.push_back(n);
    int pn = p.size();
    for (int i = 1; i < pn; i++) {
        for (int j = 0; j < 2; j++) {
            sort(s[j].begin() + p[i - 1] + 1, s[j].begin() + p[i]);
        }
    }
    return solveA();
}

int solveC() {
    int pos[2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (t[i][j] == 48) pos[i] = j;
        }
    }
    if (pos[0] > pos[1]) {
        swap(pos[0], pos[1]);
        swap(s[0], s[1]);
        swap(t[0], t[1]);
    }
    int cnt[2][2] = {};
    for (int i = 0; i < pos[1]; i++) cnt[1][s[1][i] - 48]++;
    for (int i = pos[0] + 1; i < n; i++) cnt[0][s[0][i] - 48]++;
    for (int i = 0; i <= pos[0]; i++) {
        int ch = s[0][i] - 48;
        if (cnt[1][ch]) cnt[1][ch]--, s[1][i] = s[0][i];
        else cnt[1][!ch]--, s[1][i] = !ch + 48;
    }
    for (int i = pos[1]; i < n; i++) {
        int ch = s[1][i] - 48;
        if (cnt[0][ch]) cnt[0][ch]--, s[0][i] = s[1][i];
        else cnt[0][!ch]--, s[0][i] = !ch + 48;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = pos[0] + 1; j < pos[1]; j++) {
            if (cnt[i][0]) cnt[i][0]--, s[i][j] = 48;
            else cnt[i][1]--, s[i][j] = 49;
        }
    }
    return solveA();
}

int solve() {
    cin >> n;
    cin >> s[0] >> s[1] >> t[0] >> t[1];
    int kA = true;
    int cnt[2] = {};
    for (int i = 1; i < n; i++) {
        kA &= s[0][i] == s[0][i - 1];
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (t[i][j] == 48) cnt[i]++;
        }
    }
    if (kA) return solveA(); 
    if (t[0] == t[1]) return solveB();
    if (cnt[0] == 1 && cnt[1] == 1) return solveC();
    return 0;
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    cin >> T;
    while (T--) {
        cout << solve() << endl;
    }
    return 0;
}