
int calcul_v1(int x, int y) {
	x += 2;
	int z = x + y;

	return z;
}

void calcul_v2(int x, int y) {
	x += 2;
	int z = x + y;
}

void calcul_v3(int x, int y, int z) {
	x += 2;
	z = x + y;
}

void calcul_v4(int *x, int y, int *z) {
	*x += 2;
	*z = *x + y;
}

void main() {
	int a, b, c;
	a = 7;
	b = 4;

	c = calcul_v1(a, b);
	calcul_v2(a, b);
}