
void add1(char x, char y, short int z)
{
	x += 1;
	y -= 2;
	z = x + y + 1;
}

short int add2(char x, char y)
{
	x += 1;
	y -= 2;
	short z = x + y + 1;
	
	return z;
}

int main()
{
	char a, b;
	short c = 0;

	a = 11;
	b = 12;

	add1(a, b, c);
	c = add2(a, b);
}