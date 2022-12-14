#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool succeeds(int k, long long c, int d, const vector<int>& a) {
    long long sum = 0;

    for (int i = 0; sum < c && i < d; i++) {
        int ai = i % (k + 1);
        if (ai < a.size()) sum += a[ai];
    }

    return sum >= c;
}

void solve(long long c, int d, const vector<int>& a)
{
    int low = 0, high = d;

    while (low <= high) {
        int middle = low + (high - low) / 2;

        if (succeeds(middle, c, d, a)) low = middle + 1;
        else high = middle - 1;
    }

    if (high == d) cout << "Infinity" << endl;
    else if (high == -1) cout << "Impossible" << endl;
    else cout << high << endl;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, d;
        long long c;
        cin >> n >> c >> d;

        vector<int> a(n);
        for (int j = 0; j < n; j++) cin >> a[j];

        sort(a.begin(), a.end(), greater<int>());
        solve(c, d, a);
    }
}