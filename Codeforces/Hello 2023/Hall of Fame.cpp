#include <iostream>
using namespace std;

int solve(const int& n, const string& s) {
    int r = -1, l = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R' && r == -1) r = i;
        else if (s[i] == 'L') {
            if (r >= 0) return 0;
            l = i;
        }
    }

    if (r == -1 || l == -1) return -1;
    return r;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int ans = solve(n, s);
        cout << ans << endl;
    }

    return 0;
}
