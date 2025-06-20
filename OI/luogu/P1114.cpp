#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

vector<int> a, s, t;

struct Data {
    int l = 0x7fffffff, r = 0x80000000;
    void updata(int x) {
        if (x < l) l = x;
        if (x > r) r = x;
    }

    operator int() {
        return r - l;
    }

    int operator=(int x) {
        updata(x);
        return x;
    }
};
vector<Data> m;

int main() {
    int n;
    cin >> n;
    a.assign(n + 1, 0);
    s.assign(n + 1, 0);
    t.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = a[i] + s[i - 1];
        t[i] = 2 * s[i] - i + n;
    }
    t[0] = 2 * s[0] + n;
    // for (int i : s) cout << i << "\t";
    // cout << "\n";
    // for (int i : t) cout << i << "\t";

    m.assign(2 * n + 1, {});
    for (int i = 0; i <= n; i++) {
        m[t[i]] = i;
    }
    int ans = 0;
    for (int i : m) {
        if (i > ans) ans = i;
    }
    cout << ans / 2 * 2;
}