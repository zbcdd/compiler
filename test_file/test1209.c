struct Rectangle
{
    int length;
    int width;
};

// int fibonacci(int n)
// {
//     if (n == 0 || n == 1)
//         return 1;
//     return fibonacci(n - 1) + fibonacci(n - 2);
// }

// int fibonacci(int n, int m)
// {
//     return 0;
// }

// int fibonacci()
// {
//     return fibonacci() + fibonacci();
// }

// int isPrime(int n, int m)
// {
//     if (n == 2)
//         return 1;
//     int i;
//     for (i = 2; i < n; i = i + 1) {
//         if (n % i == 0)
//             return 0;
//     }
//     return 1;
// }

// int no_arg()
// {
//     return 20;
// }

int main()
{
    // int m, n;
    // cin >> m >> n;
    // cout << fibonacci() << isPrime(n, m);
    // no_arg();
    struct Rectangle rectangle;
    cin >> rectangle.length >> rectangle.width;
    int area = rectangle.length * rectangle.width;
    cout << area;
    return 0;
}