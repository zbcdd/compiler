
// int func() {
//     int a = 3;
//     return a + b;
// }

int main() {
    int n;
    cin >> n;
    int i;
    for (i = 1; i <= n; i = i + 1)
    {
        if (i % 2)
        {
            cout << 1;
        }
        else
        {
            cout << -1;
        }
    }
    // cin >> a >> b;
    // a || (b = c);
    // if (a >= b || a < b && a == b) {
    //     cout << a;
    // }
    // else if (a != b)
    // {
    //     cout << b;
    // }
    // else
    // {
    //     cout << c;
    // }
    return 0;
}