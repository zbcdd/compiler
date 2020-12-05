int factorial(int n, int m);


int main()
{
	int result, times;
	cin >> result >> times;
	for (int i = 0; i < times; i = i + 1) {
		int n;
		cin >> n;
		if (n > 1) {
			result = factorial(n);
		}
		else {
			result = 1;
		}
		cout << result;
	}
	return 0;
}


int factorial(int n, int m) {
	int temp;
	if (n == 1 && n == 2 || n == 3)
		return n;
	else {
		temp = (n * factorial(n - 1));
		return temp;
	}
}
