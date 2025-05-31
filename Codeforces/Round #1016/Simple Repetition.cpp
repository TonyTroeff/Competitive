#include <iostream>
using namespace std;

bool is_prime(const int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

bool solve() {
    int n, k;
    cin >> n >> k;

    if (n == 1) {
        return k == 2;
    } else {
        return k == 1 && is_prime(n);
    }
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}