#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(const int& n) {
    int v = 10, ans = 0;
    while (n > v) {
        ans += 9;
        v *= 10;
    }

    ans += n / (v / 10);
    return ans;
}

int main()
{
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        cout << solve(n) << endl;
    }

    return 0;
}