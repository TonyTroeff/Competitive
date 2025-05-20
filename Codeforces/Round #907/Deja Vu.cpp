#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void solve(vector<int> &a, vector<int>& x, const vector<int> &powers) {
    int min = -1;
    for (int i = 0; i < x.size(); i++) {
        if (i != 0 && x[i] >= min) continue;

        min = x[i];

        int currentPower = powers[x[i]], additive = powers[x[i] - 1];
        for (int & el : a) {
            if (el % currentPower == 0) el += additive;
        }
    }
}

int main()
{
    int t;
    cin >> t;

    vector<int> powers(31);
    powers[0] = 1;
    for (int i = 1; i < powers.size(); i++) powers[i] = 2 * powers[i - 1];

    for (int i = 0; i < t; i++) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n), x(q);
        for (int j = 0; j < n; j++) cin >> a[j];
        for (int j = 0; j < q; j++) cin >> x[j];

        solve(a, x, powers);

        for (const int &el : a) cout << el << " ";
        cout << endl;
    }
}