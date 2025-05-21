#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > init(const int &n, const int &k, const string &s) {
    vector next(k, n + 1);
    vector jumps(n + 1, vector<int>(k));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < k; j++)
            jumps[i + 1][j] = next[j];

        next[s[i] - 'a'] = i + 1;
    }

    for (int j = 0; j < k; j++)
        jumps[0][j] = next[j];

    return jumps;
}

int find_best_next(const int &pos, const int &k, const vector<vector<int>> &jumps) {
    int best = 0;
    for (int j = 0; j < k; j++)
        if (jumps[pos][j] > jumps[pos][best]) best = j;

    return best;
}

vector<int> solve(const int &n, const int &k, const vector<vector<int>> &jumps) {
    vector<int> dp(n + 2);
    dp[n + 1] = 0;

    for (int i = n; i >= 0; i--) {
        const int best_next = find_best_next(i, k, jumps);
        const int next_pos = jumps[i][best_next];
        dp[i] = 1 + dp[next_pos];
    }

    return dp;
}

int main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<vector<int>> jumps = init(n, k, s);
    vector<int> dp = solve(n, k, jumps);

    int t;
    cin >> t;

    while (t--) {
        string q;
        cin >> q;

        int pos = 0;
        for (int i = 0; pos <= n && i < q.size(); i++)
            pos = jumps[pos][q[i] - 'a'];

        cout << dp[pos] << endl;
    }
}
