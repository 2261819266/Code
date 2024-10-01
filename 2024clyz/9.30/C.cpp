#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::string;

string a(10, '0');

int main() {
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
    sscanf(a.c_str(), "%d", &ans);
    char s[10];
    sprintf(s, "%d", (int)sqrt(ans));
    string b = s;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] > '0' && b[i] <= '9') cout << b[i] << " " << i << "\n";
    }
}