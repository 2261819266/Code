#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// istream operator>>(istream &in, __int128 &x) {
//     long long y;
//     in >> y;
//     x = y;
// }

namespace Struct {
#define int long long

struct Type {
    int SIZE = 0;
    bool is_struct;
	struct Data {
		string name;
		Type *type;
		int add;
		int operator=(int x) {
			return add = x;
		}

		Data(const string &_name = "", Type *_type = {}) : name(_name), type(_type) {}
	};

    vector<Data> a;

    Type(int x = 0) : SIZE(x), is_struct(false) {}

    int size() {
        if (SIZE) return SIZE;
        for (Data &i : a) {
            int x = i.type->size();
			if (SIZE % x) SIZE = (SIZE / x + 1) * x;
			SIZE += x;
        }
        return SIZE;
    }

	void add(Type *type, string name) {
		a.push_back({name, type});
	}
};

Type _byte(1), _short(2), _int(4), _long(8);

unordered_map<string, Type*> mp = {
    {"byte", &_byte},
    {"short", &_short},
    {"int", &_int},
    {"long", &_long},
};
vector<Type> types;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
		int op;
		cin >> op;
		if (op == 1) {
			Type newt;
			string name;
			int c;
			for (int i = 0; i < c; i++) {
				string t, s;
				cin >> t >> s;
				newt.add(mp[t], s);
			}
		}
    }
}

signed main() {
    solve();
    return 0;
}
}

signed main() {
}