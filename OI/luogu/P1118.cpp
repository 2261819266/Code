#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

vector<int> C;

void init(int n) {
    C.assign(n + 1, 0);
    C[0] = C[n] = 1;
    for (int i = 1; i * 2 <= n; i++) {
        C[i] = C[n - i] = C[i - 1] * (n - i + 1) / i;
    }
}

vector<int> a, b;
int n;

bool dfs(int s, int x = 0) {
    if (x == n) {
        if (s) return false;
        for (int j : a) cout << j << " ";
        return true;
    }
    for (int i = 0; i < n; i++) {
        if (!b[i]) {
            b[i] = true;
            a[x] = i + 1;
            bool k = dfs(s - C[x] * (i + 1), x + 1);
            if (k) return true;
            b[i] = false;
        }
    }
    return false;
}

int main() {
    int s;
    cin >> n >> s;
    init(n - 1);
    // for (int i : C) cout << i << " " ;
    a.assign(n, 0);
    b.assign(n, 0);
    dfs(s);
}