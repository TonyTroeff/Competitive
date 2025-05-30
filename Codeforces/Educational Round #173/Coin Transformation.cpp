#include <cmath>
#include <iostream>
using namespace std;

long long solve() {
    long long n;
    cin >> n;

    long long res = 1;
    while (n >= 4) {
        res *= 2;
        n /= 4;
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
