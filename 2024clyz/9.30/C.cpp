#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define int long long
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;
using std::string;

string a(25, '0');

signed main() {
    fo(root)
    int n;
    cin >> n;
    while (n--) {
        int x, y;
        cin >> x >> y;
        a[y] = x + '0';
    }
    while (a.back() == '0') a.pop_back();
    int ans = 0;
    // cout << a.c_str();
    sscanf(a.c_str(), "%lld", &ans);
    char s[10];
    sprintf(s, "%lld", (int)sqrt(ans));
    string b = s;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] > '0' && b[i] <= '9') cout << b[i] << " " << i << "\n";
    }
}