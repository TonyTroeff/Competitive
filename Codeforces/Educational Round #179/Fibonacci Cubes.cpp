#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 10

vector<int> fib(MAX_N);

void init() {
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < MAX_N; i++) fib[i] = fib[i - 1] + fib[i - 2];
}

void solve() {
    int n, m;
    cin >> n >> m;

    string ans(m, '0');

    const int d1 = fib[n - 1], d2 = d1 + fib[n - 2];
    vector<int> sides(3);
    for (int i = 0; i < m; i++) {
        cin >> sides[0] >> sides[1] >> sides[2];
        ranges::sort(sides);

        if (sides[0] >= d1 && sides[1] >= d1 && sides[2] >= d2)
            ans[i] = '1';
    }

    cout << ans << endl;
}

int main() {
    init();

    int t;
    cin >> t;

    while (t--)
        solve();
}