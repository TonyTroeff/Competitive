#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector res(n, 0);
    vector adj_freq(k, vector<int>(k));

    res[0] = 0;

    for (int i = 1; i < n; i++) {
        const int prev = res[i - 1];
        int min_index = 0;
        for (int j = 1; j < k; j++) {
            const int candidate = (prev + j) % k;
            if (adj_freq[prev][candidate] < adj_freq[prev][min_index])
                min_index = candidate;
        }

        res[i] = min_index;
        adj_freq[prev][min_index]++;
    }

    for (int i = 0; i < n; i++) cout << static_cast<char>('a' + res[i]);
    cout << endl;
}
