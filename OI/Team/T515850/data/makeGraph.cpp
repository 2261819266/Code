#include <bits/stdc++.h>
using namespace std;
#define rg register
const int maxn = 1e7 + 5, maxm = 1e3 + 5;
int n, m, cnt, fa[maxn];
char s[maxm][maxm];
int zhao(rg int xx) {
	if (fa[xx] == xx)
		return xx;
	else
		return fa[xx] = zhao(fa[xx]);
}
int main() {
	fprintf(stderr, "This program is used to generate undirected connected graphs with n nodes, m edges and K weights.\n");
	fprintf(stderr, "The program generates 100 input files by default.\n");
	fprintf(stderr, "For each input file, you must enter three parameters, N, m, and K.\n");
	fprintf(stderr, "Please make sure that 0<=n<=10000000 0<=m<=10000000 m>=n-1.\n");
	fprintf(stderr, "N is the number of nodes in the graph, M is the number of edges in the graph\n");
	fprintf(stderr, "and K is some parameters in the graph. If you do not want to output K.\n");
	fprintf(stderr, "Please delete the code yourself.\n");
	default_random_engine engine(time(NULL));
	srand(time(NULL));
	for (rg int i = 1; i <= 10; i++) {
		rg int cntt[9];
		memset(cntt, 0, sizeof(cntt));
		rg int Num = -1, now = i;
		while (now) {
			cntt[++Num] = now % 10;
			now /= 10;
		}
		s[i][0] = 'd', s[i][1] = 'a', s[i][2] = 't', s[i][3] = 'a';
		for (rg int j = 4; j <= Num + 4; j++) {
			s[i][j] = cntt[Num + 4 - j] + '0';
		}
		s[i][Num + 5] = '.', s[i][Num + 6] = 'i', s[i][Num + 7] = 'n';
	}
	for (rg int kk = 1; kk <= 100; kk++) {
		long long now = 0;
		if (kk >= 2)
			fprintf(stderr, "Last num:%d is OK\n.", kk - 1);
		fprintf(stderr, "Now the %dth set of data is generated.\n", kk);
		fprintf(stderr, "please enter n m k\n");
		fprintf(stderr, "And then waiting....\n");
		freopen(s[kk], "w", stdout);
		cnt = 0;
		rg int jl = 0, n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		uniform_int_distribution<> dis(1, 0x3f3f3f3f);
		printf("%d %d %d\n", n, m, k);
		if (m < n - 1) {
			fprintf(stderr, "Wrong!m must be bigger than n-1.\n");
			fprintf(stderr, "The %dth data is not generated.\n", kk);
			continue;
		}
		if (m < 0 || m > 10000000) {
			fprintf(stderr, "Wrong!m is too big or too small.\n");
			fprintf(stderr, "The %dth data is not generated.\n", kk);
			continue;
		}
		if (n < 0 || n > 10000000) {
			fprintf(stderr, "Wrong!n is too big or too small.\n");
			fprintf(stderr, "The %dth data is not generated.\n", kk);
			continue;
		}
		for (rg int i = 1; i <= n; i++)
			fa[i] = i;
		while (cnt < n - 1) {
			now++;
			if (now >= 10000000000) {
				fprintf(stderr, "Too large to build\n");
				jl = 1;
				break;
			}
			rg int x = dis(engine) % n + 1, y = dis(engine) % n + 1, x1 = zhao(x), y1 = zhao(y), z = 1LL * rand() * rand() % 10000000 + 1;
			if (x1 != y1) {
				fa[x1] = y1, cnt++;
				printf("%d %d\n", x, y, z);
			}
		}
		if (jl) {
			fprintf(stderr, "The %dth data is not generated.\n", kk);
			continue;
		}
		m = m - (n - 1);
		for (rg int i = 1; i <= m; i++) {
			rg int x = dis(engine) % n + 1, y = dis(engine) % n + 1, z = 1LL * rand() * rand() % 10000000 + 1;
			printf("%d %d\n", x, y, z);
		}
	}
	return 0;
}
