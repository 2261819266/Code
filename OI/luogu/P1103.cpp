#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::min;

struct Data {
    int h, w;
    operator int&() {
        return w;
    }

    bool operator<(const Data &b) const {
        return h < b.h;
    }
};

vector<Data> a;

int main() {
    int n, k;
    cin >> n >> k;
    a.assign(n + 1, {});
    for (Data &i : a) {
        cin >> i.h >> i;
    }
    sort(a.begin(), a.end());
    vector<vector<int>> f(n + 1, vector<int>(n + 1));
    k = n - k;
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            f[i][j] = 1e6;
            for (int l = j - 1; l < i; l++) {
                f[i][j] = min(f[i][j], f[l][j - 1] + abs(a[l] - a[i]));
            }
        }
    }
    int ans = 1e6;
    for (int i = k; i <= n; i++) {
        ans = min(ans, f[i][k]);
    }
    cout << ans << "\n";
}
