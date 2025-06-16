#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector matrix(n, vector<char>(m));
    for (vector<char> &row: matrix) {
        for (char &el: row) cin >> el;
    }

    vector gold(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            gold[i + 1][j + 1] = gold[i][j + 1] + gold[i + 1][j] - gold[i][j];
            if (matrix[i][j] == 'g') gold[i + 1][j + 1]++;
        }
    }

    int min_loss = gold[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != '.') continue;

            const int x1 = max(0, i - k + 1), y1 = max(0, j - k + 1);
            const int x2 = min(n, i + k), y2 = min(m, j + k);
            const int loss = gold[x2][y2] - gold[x1][y2] - gold[x2][y1] + gold[x1][y1];
            min_loss = min(min_loss, loss);
        }
    }

    cout << gold[n][m] - min_loss << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();

#ifdef SINGLE_TEST
    int t = 1;
#else
    int t;
    cin >> t;
#endif

    while (t--)
        solve();
}
