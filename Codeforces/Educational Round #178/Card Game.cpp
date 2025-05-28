#include <iostream>
#include <vector>
using namespace std;

string solve() {
    int n;
    cin >> n;

    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        a[i] = c == 'A';
    }

    vector<int> b(n + 1);
    for (int i = n - 1; i >= 0; i--)
        b[i] = b[i + 1] + !a[i];

    for (int i = 0; i < n; i++) {
        if (!a[i] || (i == n - 1 && !a[0])) continue;
        if (b[i + 1] == 0 || (i == 0 && b[i + 1] == 1 && !a[n - 1])) return "Alice";
    }

    return "Bob";
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        cout << solve() << endl;
    }
}
