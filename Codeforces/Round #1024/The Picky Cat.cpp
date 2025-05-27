#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;

        a[i] = abs(el);
    }

    const int less = static_cast<int>(ranges::count_if(a, [&pivot = a[0]](const int &el) { return el < pivot; }));
    const int median_pos = n / 2 + n % 2;
    return less < median_pos || median_pos <= n - less;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}
