#include <cstdio>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using std::cin;
using std::vector;
using std::cout;
using std::string;

int F(int x) {
	return (x - 1) * (x - 2) / 2;
}

vector<int> solve(string s) {
	int n = s.size();
	vector<int> a(1), f(n + 1), c(1, 1), fc(1, 0);
	for (int i : s) {
		a.push_back(i == ')' ? -1 : 1);
	}
	int now = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1];
		if (a[i] == 1) {
			now++;
			c.push_back(1);
			// fc
		} else {
			if (now) {
				now--;
				f[i]++;
				c.pop_back();
				int &x = *(c.end() - 1);
				f[i] += F(1 + x) - F(x);
				x++;
			} else {
				c[0] = 1;
			}
				
		}
	}
	return f;
}

int main() {
	std::string s;
	cin >> s;
	auto f = solve(s);
	for (int i : f) cout << i << " ";
}