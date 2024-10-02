#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int n;
vector<int> a, ANS;

int solve1() {
    int k = 0; // 
    for (int i = 1; i <= n; i++) {
        k += a[i] % 2;
    }
    k %= 2;
    for (int i = 1; i <= n; i++) {
        a[i] -= k;
    }
    int ans = 0;
    for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] % 2)
    }
}

int solve2() {

}

int solve() {
    return n % 2 ? solve1() : solve2();
}

int main() {
    cin >> n;
    a.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    solve();
}