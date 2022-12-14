#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

void initialDfs(int node, int runningXor, int previous, int stopNode, set<int>& xorSet, const unordered_map<int, vector<pair<int, int>>>& connections) {
    xorSet.insert(runningXor);

    vector<pair<int, int>> next = connections.find(node)->second;
    for (int i = 0; i < next.size(); i++) {
        int v = next[i].first, w = next[i].second;
        if (previous == v || stopNode == v) continue;
        initialDfs(v, runningXor ^ w, node, stopNode, xorSet, connections);
    }
}

bool finalDfs(int node, int runningXor, int previous, const set<int>& xorSet, const unordered_map<int, vector<pair<int, int>>>& connections) {
    if (previous != -1 && xorSet.find(runningXor) != xorSet.end()) return true;

    vector<pair<int, int>> next = connections.find(node)->second;
    for (int i = 0; i < next.size(); i++) {
        int v = next[i].first, w = next[i].second;
        if (previous == v) continue;

        if (finalDfs(v, runningXor ^ w, node, xorSet, connections)) return true;
    }

    return false;
}


bool solve(int a, int b, const unordered_map<int, vector<pair<int, int>>>& connections) {
    set<int> xorSet;
    initialDfs(a, 0, -1, b, xorSet, connections);
    return finalDfs(b, 0, -1, xorSet, connections);
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, a, b;
        cin >> n >> a >> b;

        unordered_map<int, vector<pair<int, int>>> connections;
        for (int j = 0; j < n - 1; j++) connections[j] = vector<pair<int, int>>();
        for (int j = 0; j < n - 1; j++) {
            int u, v, w;
            cin >> u >> v >> w;

            connections[u].push_back(make_pair(v, w));
            connections[v].push_back(make_pair(u, w));
        }

        bool success = solve(a, b, connections);
        if (success) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}