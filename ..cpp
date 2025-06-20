#include <vector>
#include <iostream>

class SegmentTree {
private:
	std::vector<long long> tree, lazy, lazyMul;
	int n;

	// Removed duplicate pushDown method to resolve redeclaration error.

	void buildTree(const std::vector<long long>& arr, int node, int start, int end) {
		if (start == end) {
			tree[node] = arr[start];
		} else {
			int mid = (start + end) / 2;
			buildTree(arr, node * 2, start, mid);
			buildTree(arr, node * 2 + 1, mid + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}

	void pushDown(int node, int start, int end) {
		if (lazy[node] != 0 || lazyMul[node] != 1) {
			tree[node] = (tree[node] * lazyMul[node] + lazy[node] * (end - start + 1)) % mod;
			if (start != end) {
				lazyMul[node * 2] = (lazyMul[node * 2] * lazyMul[node]) % mod;
				lazyMul[node * 2 + 1] = (lazyMul[node * 2 + 1] * lazyMul[node]) % mod;
				lazy[node * 2] = (lazy[node * 2] * lazyMul[node] + lazy[node]) % mod;
				lazy[node * 2 + 1] = (lazy[node * 2 + 1] * lazyMul[node] + lazy[node]) % mod;
			}
			lazy[node] = 0;
			lazyMul[node] = 1;
		}
	}

	void updateRangeMul(int node, int start, int end, int l, int r, long long val) {
		pushDown(node, start, end);
		if (start > r || end < l) return;
		if (start >= l && end <= r) {
			lazyMul[node] = (lazyMul[node] * val) % mod;
			lazy[node] = (lazy[node] * val) % mod;
			pushDown(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		updateRangeMul(node * 2, start, mid, l, r, val);
		updateRangeMul(node * 2 + 1, mid + 1, end, l, r, val);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % mod;
	}

	void updateRangeAdd(int node, int start, int end, int l, int r, long long val) {
		pushDown(node, start, end);
		if (start > r || end < l) return;
		if (start >= l && end <= r) {
			lazy[node] = (lazy[node] + val) % mod;
			pushDown(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		updateRangeAdd(node * 2, start, mid, l, r, val);
		updateRangeAdd(node * 2 + 1, mid + 1, end, l, r, val);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % mod;
	}

	long long queryRange(int node, int start, int end, int l, int r) {
		pushDown(node, start, end);
		if (start > r || end < l) return 0;
		if (start >= l && end <= r) return tree[node];
		int mid = (start + end) / 2;
		return (queryRange(node * 2, start, mid, l, r) + queryRange(node * 2 + 1, mid + 1, end, l, r)) % mod;
	}

public:
	long long mod;
	SegmentTree(const std::vector<long long>& arr, long long m) : n(arr.size()), mod(m) {
		tree.resize(4 * n, 0);
		lazy.resize(4 * n, 0);
		lazyMul.resize(4 * n, 1);
		buildTree(arr, 1, 0, n - 1);
	}

	void updateMul(int l, int r, long long val) {
		updateRangeMul(1, 0, n - 1, l, r, val);
	}

	void updateAdd(int l, int r, long long val) {
		updateRangeAdd(1, 0, n - 1, l, r, val);
	}

	long long query(int l, int r) {
		return queryRange(1, 0, n - 1, l, r);
	}
};