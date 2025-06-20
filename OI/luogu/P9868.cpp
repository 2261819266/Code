#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::sort;

vector<string> a, b, c;

int main() {
    int n, m;
    cin >> n >> m;
    a.assign(n, "");
    b.assign(n, "");
    c.assign(n, "");

    for (string &s : a) {
        cin >> s;
    }

    string t(m, 'z');
    for (int i = 0; i < n; i++) {
        b[i] = c[i] = a[i];
        sort(b[i].begin(), b[i].end());
        sort(c[i].begin(), c[i].end(), [](char x, char y) { return x > y; });
        if (c[i] < t) t = c[i];
    }
    for (int i = 0; i < n; i++) {
        bool ans = 1;
        if (t < b[i]) ans = 0;
        cout << ans;
    }
}