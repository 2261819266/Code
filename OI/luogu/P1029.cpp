#include <cstdio>

int gcd(int x, int y) {
	if (x % y)
		return gcd(y, x % y);
	return y;
}

int main() {
#ifdef LOCAL
	freopen("D:\\code\\in.in", "r", stdin);
	freopen("D:\\code\\out.out", "w", stdout);
#endif
	int x, y, ans = 0;
	scanf("%d%d", &x, &y);
	int z = x * y;
	for (int i = x; i < z; i += x) {
		int j = z / i;
		if (i * j == z && gcd(i, j) == x)
			ans++;
	}
	printf("%d", ans);
}