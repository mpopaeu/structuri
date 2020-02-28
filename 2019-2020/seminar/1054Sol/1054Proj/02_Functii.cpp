


int suma_v1(int x, int y) {
	x += 1;
	int z = x + y;

	return z;
}

void suma_v2(int x, int y) {
	x += 1;
	int z = x + y;
}

void suma_v3(int x, int y, int z) {
	x += 1;
	z = x + y;
}

void suma_v4(int* x, int y, int* z) {
	*x += 1;
	*z = *x + y;
}

void main() {
	int a, b, c;

	a = 5;
	b = 7;

	c = suma_v1(a, b);
	suma_v2(a, b);
	suma_v3(a, b, c);
}