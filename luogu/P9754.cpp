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
#define endl "\n"

struct Type {
    int SIZE = 0;
	int align = 0;
    bool is_struct;
	struct Data {
		string name;
		Type *type;
		int addr;
		int operator=(int x) {
			return addr = x;
		}

		Data(const string &_name = "", Type *_type = {}) : name(_name), type(_type) {}
	};

    vector<Data> a;
	// unordered_map<string, Data*> md;

    Type(int x = 0) : SIZE(x), align(x), is_struct(false) {}

    int size() {
        if (SIZE) return SIZE;
        for (Data &i : a) {
            int x = i.type->size(), y = i.type->align;
			if (SIZE % y) SIZE = (SIZE / y + 1) * y;
			i.addr = SIZE;
			SIZE += x;
			if (y > align) align = y;
        }
        return SIZE;
    }

	void add(Type *type, string name) {
		a.push_back({name, type});
	}

	// Data *find(const string s) {
	// 	return md[s];
	// }
};

Type _byte(1), _short(2), _int(4), _long(8);

const int maxn = 101;

unordered_map<string, Type*> mt = {
    {"byte", &_byte},
    {"short", &_short},
    {"int", &_int},
    {"long", &_long},
};
vector<Type> types(maxn);
int cnt_types;

int addrcnt;
struct Node {
	Type *type;
	string name;
	int addr;

	Node(Type *t, string s) {
		type = t;
		name = s;
		int x = t->SIZE, y = t->align;
		if (addrcnt % y) (((addrcnt /= y) += 1) *= y);
		addr = addrcnt;
		addrcnt += x; 
	}
};

unordered_map<string, Node*> ma;
vector<Node> a;

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
			cin >> name >> c;
			for (int j = 0; j < c; j++) {
				string t, s;
				cin >> t >> s;
				newt.add(mt[t], s);
			}
			newt.size();
			types[cnt_types] = newt;
			mt[name] = &types[cnt_types++];
			cout << newt.size() << " " << newt.align << endl;
		} else if (op == 2) {
			string t, s;
			cin >> t >> s;
			a.push_back({mt[t], s});
			ma[s] = &a[a.size() - 1];
			cout << a.back().addr << endl;
		} else if (op == 3) {
			string s;
			cin >> s;
			vector<string> v;
			string t;
			for (int j : s) {
				if (j == '.') v.push_back(t), t.clear();
				else t += j;
			}
			v.push_back(t);
			// for (string i : v) cout << i << endl;
			int ans = ma[v.front()]->addr;
			Type *p = ma[v.front()]->type;
			for (int j = 1; j < v.size(); j++) {
				Type::Data q;
 				for (auto k : p->a) {
		 			if (k.name == v[j]) q = k;
				}
				ans += q.addr;
				p = q.type;
			}
			cout << ans << endl;
		} else if (op == 4) {
			
		}
    }
}

signed main() {
    solve();
    return 0;
}
}

signed main() {
	return Struct::main();
}