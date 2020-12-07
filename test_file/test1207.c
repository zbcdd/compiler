// int func() {
//     int a = 3;
//     return a + b;
// }

int main() {
    int a, b, c;
    cin >> a >> b;
    if (a >= b || a < b && a == b) {
        cout << a;
    }
    else if (a != b)
    {
        cout << b;
    }
    else
    {
        cout << c;
    }
    
    return 0;
}