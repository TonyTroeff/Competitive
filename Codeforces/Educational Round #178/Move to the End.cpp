#include <iostream>
#include <vector>
using namespace std;

vector<long long> solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> lmax(n + 1);
    for (int i = 0; i < n; i++) lmax[i + 1] = max(lmax[i], a[i]);

    vector<long long> res(n);
    long long sum = 0;
    for (int k = 0; k < n; k++) {
        res[k] = sum + lmax[n - (k + 1)];
        sum += a[n - (k + 1)];
        res[k] = max(res[k], sum);
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        vector<long long> res = solve();

        for (const long long &el: res) cout << el << ' ';
        cout << endl;
    }
}
