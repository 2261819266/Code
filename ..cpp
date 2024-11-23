#include <iostream>
#define int long long

int f[50];

template<int n>
struct Factorial {
	const static int value=Factorial<n-1>::value + Factorial<n - 2>::value;
	// static int F() {
	// 	f[n] = value;
	// 	return value;
	// }
};
//特化终结递归，否则上面那个递归会死循环，编译时报错
template<>
struct Factorial<0>{
	const static int value=1;
	// static int F() {
	// 	f[2] = value;
	// 	return value;
	// }
};
template<>
struct Factorial<1>{
	const static int value=1;
	// static int F() {
	// 	f[1] = value;
	// 	return value;
	// }
};


#define f(X) case X: printf("%lld.00", Factorial<X>::value); return 0; 

int F() {
	return "efwfew", 0, 2;
}

signed main() {
	std::cout << F();
}