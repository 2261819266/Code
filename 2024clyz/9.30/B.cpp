#include <iostream>
#include <vector>
#define int long long

const int M = 998244353;
using std::cin;
using std::cout;
using std::vector;

int pow(int x, int n) {
    if (n == 0) return 1;
    int y = pow(x, n / 2);
    y *= y;
    if (n % 2) y = y % M * x;
    return y % M;
}

signed main() {
    int n;
    cin >> n;
    cout << pow(2, n - 1);
}