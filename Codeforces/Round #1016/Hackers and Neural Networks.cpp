#include <iostream>
#include <vector>
using namespace std;

int solve() {
    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector b(m, vector<string>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> b[i][j];

    vector has_match(n, false);
    int best_matches = 0;
    for (int i = 0; i < m; i++) {
        int matches = 0;
        for (int j = 0; j < n; j++) {
            if (b[i][j] == a[j]) {
                matches++;
                has_match[j] = true;
            }
        }

        best_matches = max(best_matches, matches);
    }

    for (int i = 0; i < n; i++)
        if (!has_match[i])
            return -1;

    return 3 * n - 2 * best_matches;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
