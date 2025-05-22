#include <iostream>
#include <vector>
using namespace std;

vector<bool> read_bits(const int n) {
    vector<bool> res(n);

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        res[i] = c == '1';
    }

    return res;
}

bool can_connect(const int index, const int partition, const int start, const int end,
                 const vector<vector<pair<int, int>>> &partitions,
                 vector<vector<bool>> &used) {
    return !used[index][partition] && partitions[index][partition].first <= end && partitions[index][partition].second
           >= start;
}

long long solve(const int index, const int partition, const int n, const vector<vector<pair<int, int>>> &partitions,
          vector<vector<bool>> &used) {
    const int start = partitions[index][partition].first, end = partitions[index][partition].second;
    long long count = end - start + 1;

    used[index][partition] = true;

    if (index > 0) {
        const int prev_index = index - 1;
        for (int i = 0; i < partitions[prev_index].size(); i++) {
            if (can_connect(prev_index, i, start, end, partitions, used))
                count += solve(prev_index, i, n, partitions, used);
        }
    }

    if (index < n - 1) {
        const int next_index = index + 1;
        for (int i = 0; i < partitions[next_index].size(); i++) {
            if (can_connect(next_index, i, start, end, partitions, used))
                count += solve(next_index, i, n, partitions, used);
        }
    }

    return count;
}

long long solve() {
    int n;
    cin >> n;

    vector<bool> bits = read_bits(n);

    vector<vector<pair<int, int>>> partitions(n);
    for (int i = 0; i < n; i++) {
        if (bits[i] == 1) {
            partitions[i].emplace_back(i, i);
        } else {
            if (i > 0) partitions[i].emplace_back(0, i - 1);
            if (i < n - 1) partitions[i].emplace_back(i + 1, n - 1);
        }
    }

    vector<vector<bool>> used;
    for (int i = 0; i < n; i++)
        used.emplace_back(partitions[i].size(), false);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < partitions[i].size(); j++) {
            if (!used[i][j]) ans = max(ans, solve(i, j, n, partitions, used));
        }
    }

    return ans;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
