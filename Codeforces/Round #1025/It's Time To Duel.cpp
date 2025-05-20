#include <iostream>
#include <vector>
using namespace std;

bool solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& el : a) cin >> el;

    int zeros = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (i > 0 && a[i - 1] == 0) return true;
            zeros++;
        }
    }

    return zeros == 0 || zeros == n;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        if (solve()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
