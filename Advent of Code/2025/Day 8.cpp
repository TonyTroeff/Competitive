#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

struct disjoint_set {
    vector<int> group, size;
    int count;

    explicit disjoint_set(const int n) : group(n), size(n, 1), count(n) {
        for (int i = 0; i < n; i++) group[i] = i;
    }

    int find(const int x) {
        if (group[x] == x) return x;
        return group[x] = find(group[x]);
    }

    void connect(const int a, const int b) {
        int g1 = find(a), g2 = find(b);
        if (g1 == g2) return;

        if (size[g1] < size[g2]) swap(g1, g2);

        group[g2] = g1;
        size[g1] += size[g2];
        size[g2] = 0;
        count--;
    }
};

struct junction_box {
    ll x, y, z;
};

struct connection {
    ll distance;
    int from, to;
};

ll calculate_distance(const junction_box &from, const junction_box &to) {
    const ll a = from.x - to.x, b = from.y - to.y, c = from.z - to.z;
    return a * a + b * b + c * c;
}

ll solve_part_one(const vector<junction_box> &junction_boxes, const vector<connection> &connections) {
    disjoint_set dsu(static_cast<int>(junction_boxes.size()));
    for (int i = 0; i < 1000; i++)
        dsu.connect(connections[i].from, connections[i].to);

    vector<int> top_sizes(3);
    ranges::partial_sort_copy(dsu.size, top_sizes, greater());

    return top_sizes[0] * top_sizes[1] * top_sizes[2];
}

ll solve_part_two(const vector<junction_box> &junction_boxes, const vector<connection> &connections) {
    disjoint_set dsu(static_cast<int>(junction_boxes.size()));
    int index = 0;
    while (dsu.count > 1) {
        dsu.connect(connections[index].from, connections[index].to);
        index++;
    }

    return junction_boxes[connections[index - 1].from].x * junction_boxes[connections[index - 1].to].x;
}

int main() {
    ifstream in("Day 8.input.txt");

    vector<junction_box> junction_boxes;
    while (!in.eof()) {
        string line;
        getline(in, line);

        istringstream iss(line);
        ll x, y, z;
        iss >> x;
        iss.ignore(1, ',');
        iss >> y;
        iss.ignore(1, ',');
        iss >> z;

        junction_boxes.push_back({x, y, z});
    }

    vector<connection> connections;
    for (int i = 0; i < junction_boxes.size(); i++) {
        for (int j = i + 1; j < junction_boxes.size(); j++)
            connections.push_back({calculate_distance(junction_boxes[i], junction_boxes[j]), i, j});
    }

    ranges::sort(connections, [](const connection &a, const connection &b) { return a.distance < b.distance; });

    cout << "Part one: " << solve_part_one(junction_boxes, connections) << endl;
    cout << "Part two: " << solve_part_two(junction_boxes, connections) << endl;

    return 0;
}
