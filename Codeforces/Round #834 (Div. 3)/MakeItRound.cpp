#include <iostream>
using namespace std;

long long solve(const long long& n, const long long& m) {
    int count2 = 0, count5 = 0;

    long long t = n;
    while (t > 0 && t % 2 == 0) { count2++; t /= 2; }
    while (t > 0 && t % 5 == 0) { count5++; t /= 5; }

    long long k = 1;
    while (count2 < count5 && k * 2 <= m) { count2++; k *= 2; }
    while (count5 < count2 && k * 5 <= m) {count5++; k *= 5; }

    while (k * 10 <= m) k *= 10;

    if (k == 1) return n * m;

    k *= m / k; // We need to obtain the maximum value possible.
    return n * k;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n, m;
        cin >> n >> m;

        cout << solve(n, m) << endl;
    }

    return 0;
}