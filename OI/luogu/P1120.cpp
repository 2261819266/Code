#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

vector<int> f;

bool find(const vector<int> &t, int x) {
    if (f[x] >= 0) return f[x];
    if (t[x]) return f[x] = true;
    for (int i = 0; i < t.size(); i++) {
        if (t[i] && find(t, i)) return f[x] = true;
    }
    return f[x] = false;
}

bool check(const vector<int> &t, int x) {
    bool ans = true;
    for (int i = 0; i < t.size(); i++) {
        if (t[i]) ans &= find(t, i);
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n), t;
    int sum = 0;
    for (int &i : a) cin >> i, sum += i;
    sort(a.begin(), a.end());
    f.assign(sum + 1, -1);
    t.assign(sum + 1, 0);
    for (int i : a) t[i]++;
    for (int i = a.back(); i <= sum; i++) {
        if (sum % i) continue;
        if (check(t, i)) {
            cout << i;
            return 0;
        }
    }
}