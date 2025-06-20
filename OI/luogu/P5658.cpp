#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::string;
#define int long long

vector<int> fa, f, a(1, -1);
vector<vector<int>> s;

int F(int x) {
	return (x - 1) * (x - 2) / 2;
}

vector<int> solve(string str) {
	int n = str.size();
	vector<int> A(1), dp(n + 1), c(1, 1), fc(1, 0);
	for (int i : str) {
		A.push_back(i == ')' ? -1 : 1);
	}
	int now = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1];
		if (A[i] == 1) {
			now++;
			c.push_back(1);
			// fc
		} else {
			if (now) {
				now--;
				dp[i]++;
				c.pop_back();
				int &x = *(c.end() - 1);
				dp[i] += F(1 + x) - F(x);
				x++;
			} else {
				c[0] = 1;
			}
				
		}
	}
	return dp;
}

signed main() {
    int n;
    cin >> n;
    f.assign(n + 1, -1);
    fa.assign(n + 1, 0);
    s.assign(n + 1, vector<int>());
    string str;
    cin >> str;
    for (int i : str) a.push_back(i == ')'); 
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        s[fa[i]].push_back(i);
    }
    fa[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (s[i].empty()) {
            string ss;
            for (int u = i; u; u = fa[u]) {
                ss.push_back(a[u] ? ')' : '(');
            }
            for (int j = 0, l = ss.size(); j * 2 < l; j++) {
                std::swap(ss[j], ss[l - j - 1]);
            }
            vector<int> ff = solve(ss);
            for (int j = ff.size() - 1, u = i; j >= 0; j--, u = fa[u]) {
                f[u] = ff[j];
            }
        }
    }
    
    // for (int i = 1; i <= n; i++) {
    //     cout << f[i] << " ";
    // }

    int ans = 0;
    
    for (int i = 1; i <= n; i++) {
        ans ^= i * f[i];
    }
    cout << ans;
}