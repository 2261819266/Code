#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using std::set;
using std::cin;
using std::cout;
using std::vector;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1, 0), f(n + 1, 1), d(n + 1, 1);
    for (int &i : a) {
        cin >> i;
    }
    int ans = 0, ansi = 0;
    n++;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i] && f[j] + 1 >= f[i]) {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > 1) d[i] = 0;
        set<int> s;
        for (int j = i - 1; j >=  0; j--) {
            if (f[i] == f[j] + 1 && a[j] > a[i] && s.find(a[j]) == s.end()) {
                d[i] += d[j];
                s.insert(a[j]);
            }
        }
        if (f[i] > f[ansi]) ansi = i;
    }
    // for (int i = 0; i < n; i++) {
    //     if (f[i] == f[ansi]) ans += d[i];
    //     cout << f[i] << " " << d[i] << "\n";
    // }
    cout << f[n - 1] - 1 << " " << d[n - 1] << "\n";
}