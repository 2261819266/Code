#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::sort;
using std::vector;
using std::string;

template<typename t>
vector<int> getRank(vector<t> a) {
    struct __data {
        t x;
        int i;
        bool operator<(const __data &b) const {
            return x < b.x;
        }

        bool operator>(const __data &b) const {
            return b < *this;
        }

        bool operator!=(const __data &b) const {
            return x != b.x;
        }
    };
    int n = a.size();
    vector<__data> A(n);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        A[i] = {a[i], i};
    }
    sort(A.begin(), A.end());
    for (int i = 0, j = 0; i < n; i++) {
        ans[A[i].i] = j;
        if (A[i] != A[i + 1]) j++;
    }
    return ans;
}

int main() {
    int n;
    string s;
    cin >> s;
    n = s.size();
    vector<int> a;
    for (int i : s) a.push_back(i);
    a = getRank(a);
    for (int i = 1; i < n; i *= 2) {
        vector<vector<int>> b(n);
        for (int j = 0; j < n; j++) {
            b[j].push_back(a[j]);
            b[j].push_back(a[j + i]);
        }
        a = getRank(b);
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[a[i]] = i;
    }
    for (int i : b) cout << i + 1 << " ";
}