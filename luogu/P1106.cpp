#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    string s;
    cin >> s;
    vector<int> a;
    int n, m;
    cin >> n;
    m = s.length() - n;
    for (int i : s) {
        if (a.empty() || !n) {
            a.push_back(i);
            continue;
        }
        while (!a.empty() && i < a.back() && n) {
            a.pop_back();
            n--;
        }
        a.push_back(i);
    }
    bool k = true;
    for (int i = 0; i < m; i++) {
        if (k && a[i] != '0') k = false;
        if (!k) cout << a[i] - '0';
    }
    if (k == true) cout << 0;
}