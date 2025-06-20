#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
    int n, L, R, l = 0, r = 0;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (int &i : a) {
        cin >> i;
        sum += i;
    }
    cin >> L >> R;
    sort(a.begin(), a.end());
    if (L * n > sum || R * n < sum) {
        cout << -1;
        return 0;
    }
    for (int i : a) {
        if (i < L) l += L - i;
        if (i > R) r += i - R;
    }
    cout << std::max(l, r);
}