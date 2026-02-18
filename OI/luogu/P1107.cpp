#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, h, delta;
    cin >> n >> h >> delta;
    vector<vector<int>> a(n, vector<int>(h + 1, 0)), f(n, vector<int>(h + 1, 0));
    for (vector<int> &i : a) {
        int N;
        cin >> N;
        while (N--) {
            int x;
            cin >> x;
            i[x]++;
        }
    }
    for (int i = 0; i < n; i++) {
        f[i][1] = a[i][1];
    }
    for (int i = 2; i <= h; i++) {
        int m = 0;
        if (i > delta) {
            for (int j = 0; j < n; j++) {
                m = max(m, f[j][i - delta]);
            }
        }
        for (int j = 0; j < n; j++) {
            f[j][i] = max(m, f[j][i - 1]) + a[j][i];
        } 
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, f[i][h]);
    }
    cout << ans;
}