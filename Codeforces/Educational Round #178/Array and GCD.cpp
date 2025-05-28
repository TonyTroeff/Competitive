#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 1e7

vector<int> generate_primes() {
    vector is_prime(MAX, true);
    for (int p = 2; p * p < MAX; p++) {
        if (!is_prime[p]) continue;

        for (int i = p * p; i < MAX; i += p)
            is_prime[i] = false;
    }

    vector<int> primes;
    for (int p = 2; p < MAX; p++)
        if (is_prime[p]) primes.push_back(p);

    return primes;
}

int solve(const vector<int>& primes) {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& el: a) cin >> el;

    ranges::sort(a);

    int possible = 0;
    long long sum = 0, required = 0;
    while (possible < n) {
        sum += a[n - (possible + 1)];
        required += primes[possible];

        if (sum < required) break;
        possible++;
    }

    return n - possible;
}

int main() {
    int t;
    cin >> t;

    const vector<int> primes = generate_primes();
    while (t--) {
        const int res = solve(primes);
        cout << res << endl;
    }
}