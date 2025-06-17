#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

#define INF 10000
#define STATES_COUNT 4
#define UNBOUNDED_START_BITMASK 0b10
#define UNBOUNDED_END_BITMASK 0b01

// #define SINGLE_TEST

void init() {
}

void solve() {
    string l, r;
    cin >> l >> r;

    const int n = static_cast<int>(l.size());
    vector dp(n + 1, vector(STATES_COUNT, INF));

    for (int j = 0; j < STATES_COUNT; j++) dp[n][j] = 0;

    for (int i = n - 1; i >= 0; i--) {
        const int ld = l[i] - '0', rd = r[i] - '0';

        for (int j = 0; j < STATES_COUNT; j++) {
            const bool unbounded_start = (j & UNBOUNDED_START_BITMASK) != 0, unbounded_end = (j & UNBOUNDED_END_BITMASK) != 0;
            const int start = unbounded_start ? 0 : ld, end = unbounded_end ? 9 : rd;

            for (int k = start; k <= end; k++) {
                const bool eq_l = k == ld, eq_r = k == rd;

                int next_state = 0;
                if (unbounded_start || !eq_l) next_state = next_state | UNBOUNDED_START_BITMASK;
                if (unbounded_end || !eq_r) next_state = next_state | UNBOUNDED_END_BITMASK;

                dp[i][j] = min(dp[i][j], dp[i + 1][next_state] + eq_l + eq_r);
            }
        }
    }
    cout << dp[0][0] << endl;
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