#include <cmath>
#include <iostream>
#define ll long long

using namespace std;

int main() {
#ifdef LOCAL
	freopen("D:\\code\\in.in", "r", stdin);
	freopen("D:\\code\\out.out", "w", stdout);
#endif
	ll n, k, x, y;
	cin >> n >> k >> x >> y;
	n = 4 * n * n;
	printf("%d", k / n);
}