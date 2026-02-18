#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

#define ll long long

ll solve1(string s) {
    int n = s.size();
    ll ans = 0;
    for (int k = 2; k <= n / 2; k++) {
        ans += (k - 1) * (n - 2 * k + 1);
    }
    return ans;
}

ll solve(string s) {
    int n = s.size();
    return solve1(s);
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }
}