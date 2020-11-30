struct {
    int a;
    int b;
    int c;
};

struct x {
    int a, b;
    int c;
};

void main() {
    
    int *a, b, *c, d;
    struct x mystruct;

    cin >> *a >> b >> *c >> d;
    cout << *a;

    if (a == c && b == d) {
        if ((a == c) && (b == d)) {
            *a = d;
            c = b;
        } else {
            b = c;
        }
        if (a == b || c == d) {
            *a = *c; 
        }
    }
    return 0;
}
