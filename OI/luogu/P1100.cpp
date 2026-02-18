#include <iostream>

using std::cin;
using std::cout;

int main() {
    unsigned int a;
    cin >> a;
    cout << ((a << 16) + (a >> 16)) << "\n";
}