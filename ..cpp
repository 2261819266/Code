#include <DS/SegTree.h>
#include <IO/FastIO.h>

#define int long long

signed main() {
	int n, m;
	cin >> n >> m;
	OY::VectorSegLazySumTree<int, int> a(n, [](int) { int num; cin >> num; return num; });
	while (m--) {
		int k, l, r, x;
		cin >> k >> l >> r;
		if (k == 1) {cin >> x; a.add(l - 1, r - 1, x);}
		else cout << a.query(l - 1, r - 1) << endl;
	}
}