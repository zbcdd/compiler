/*看看comment*/
//commnet
int main()
{
    /*这是
    测试用的
    样例*/
	int i = -32, j, t = 18, flag;
	int prime[100];
	prime[0] = -2;
	while (i <= 100) {
        // 循环
        /////循环
		j = 2;
		flag = 0;
		while (j < i) {
			if (!(i % j))
				flag = 1;
			j = j + 1;
		}
		if (flag == 0) {
			prime[t] = i;
			t = t + 1;
		}
		i = i + 1;
	}
	j = 0;
	while (j < t) {
		cout << prime[j];
		j = j + 1;
	}
	return 0;
}
/*看看comment*/
//comment
