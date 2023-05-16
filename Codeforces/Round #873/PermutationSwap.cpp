#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int solve(const vector<int>& p)
{
    int ans = 0;
    for (int i = 0; i < p.size(); i++)
        ans = gcd(ans, abs(p[i] - (i + 1)));

    return ans;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> p(n);
        for (int j = 0; j < n; j++) cin >> p[j];

        int ans = solve(p);
        cout << ans << endl;
    }
}