#include <cstdio>

int T, n, c[109];

double calc(double k) {
	double sum = 0., d = 1.;
	for (int i = n; ~i; --i) {
		sum += c[i] * d;
		d *= k;
	}
	return sum;
}

int main() {
	scanf("%d", &T);
	for (int tT = 1; tT <= T; ++tT) {
		scanf("%d", &n);
		for (int i = 0; i <= n; ++i) scanf("%d", c + i);
		c[0] = -c[0];
		double l = 0., r = 2., m;
		int cnt = 60;
		while (cnt--) {
			m = (l + r) * .5;
			if (calc(m) < 0.) r = m;
			else l = m;
		}
		printf("Case #%d: %.10f\n", tT, m - 1.);
	}
	return 0;
}

