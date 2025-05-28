#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// NOTE: 10^n + 1 is not divisible by either 2 or 5.
pair<int, int> solve() {
    int a, b, c;
    cin >> a >> b >> c;

    const int gcd = pow(10, c - 1);
    const int x_base = pow(10, a - c), y_base = pow(10, b - c);

    return make_pair(x_base * gcd, (y_base + 1) * gcd);
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const auto [x, y] = solve();
        cout << x << ' ' << y << endl;
    }
}
