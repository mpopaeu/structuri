



int calcul_1(int x, int y) {
	x += 1;
	int z = x + y;

	return z;
}

void calcul_2(int x, int y) {
	x += 1;
	int z = x + y;
}

void calcul_3(int x, int y, int z) {
	x += 1;
	z = x + y;
}

void calcul_4(int* x, int y, int* z) {
	*x += 1;
	*z = *x + y;
}


void main() {
	int a, b, c;
	a = 9;
	b = 0x02;

	c = calcul_1(a, b);
	calcul_2(a, b);

	calcul_4(&a, b, &c);
}