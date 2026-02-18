void f(int x) {
	int y;
	if (1) {
		int &x = y;
		x++;
	}
	y++;
}

int main() {
//	int x;
}