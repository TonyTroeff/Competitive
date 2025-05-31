#include <iostream>
#include <vector>
using namespace std;

#define MOD 998244353
#define MAX_N (1e5 + 1)
#define ll long long

vector<ll> powers_of_2(MAX_N);

void initialize_powers_of_2() {
    powers_of_2[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        powers_of_2[i] = powers_of_2[i - 1] * 2 % MOD;
}

void solve() {
    int n;
    cin >> n;

    vector<int> p(n), q(n);
    for (int& el : p) cin >> el;
    for (int& el : q) cin >> el;

    int p_max_index = 0, q_max_index = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] > p[p_max_index]) p_max_index = i;
        if (q[i] > q[q_max_index]) q_max_index = i;

        ll curr;
        if (p[p_max_index] > q[q_max_index] || (p[p_max_index] == q[q_max_index] && q[i - p_max_index] > p[i - q_max_index]))
            curr = powers_of_2[p[p_max_index]] + powers_of_2[q[i - p_max_index]];
        else
            curr = powers_of_2[p[i - q_max_index]] + powers_of_2[q[q_max_index]];

        cout << curr % MOD << ' ';
    }
    cout << endl;
}

int main() {
    initialize_powers_of_2();

    int t;
    cin >> t;

    while (t--)
        solve();
}