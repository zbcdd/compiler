int func() {
    int a = 3;
    return a + b;
}

int main() {
    int a, b;
    cin >> a >> b;
    while (a <= b || a < b || a > b || a >= b || a == b) {
        cout << a;
    }
    return 0;
}