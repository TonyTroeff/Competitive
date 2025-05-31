#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define UNKNOWN (-1)

int solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    int target = a[0];
    for (int i = 1; i < n; i++)
        target = gcd(target, a[i]);

    int count = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == target) count++;

    if (count > 0) return n - count;

    if (target != 1) {
        for (int i = 0; i < n; i++) a[i] /= target;
    }

    unordered_set<int> seen;
    vector<int> seq;
    for (int i = 0; i < n; i++) {
        if (seen.contains(a[i])) continue;

        seen.insert(a[i]);
        seq.push_back(a[i]);
    }

    ranges::sort(seq);

    vector dp(seq[seq.size() - 1] + 1, UNKNOWN);
    queue<int> q;
    for (const int &el: seq) {
        dp[el] = 0;
        q.push(el);
    }

    while (dp[1] == UNKNOWN) {
        const int current = q.front();
        q.pop();

        for (const int &el: seq) {
            const int next = gcd(current, el);
            if (dp[next] == UNKNOWN) {
                dp[next] = dp[current] + 1;
                if (next == 1) break;

                q.push(next);
            }
        }
    }

    return dp[1] + n - 1;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
