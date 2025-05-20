#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;

int solve(const int& n, const vector<int>& a, vector<int>& b)
{
    vector<int> pos(n + 1);

    sort(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        int l = 0, h = n - 1;
        while (l <= h) {
            int m = l + (h - l) / 2;
            if (b[m] < a[i]) l = m + 1;
            else h = m - 1;
        }

        pos[l]++;
    }

    long long ans = 1;
    int s = pos[n];
    for (int i = n - 1; i >= 0 && ans != 0; i--) {
        ans = (ans * s) % mod;
        s += pos[i] - 1;
    }
    return (int)ans;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (int j = 0; j < n; j++) cin >> a[j];
        for (int j = 0; j < n; j++) cin >> b[j];

        int ans = solve(n, a, b);
        cout << ans << endl;
    }
}