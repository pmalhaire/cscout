struct a {
	int a;
	int b;
};

struct b {
	int a;
	int b;
};


main()
{
	struct a *a;
	struct b b[10];

	a->a = a->b = 4;
	b[1].a = b[2].b = 42;
}
