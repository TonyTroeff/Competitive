#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

struct point {
    ll x, y;
};

struct wall {
    ll from, to;
};

ll solve_part_one(const vector<point> &points) {
    ll ans = 0;

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            ans = max(ans, (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1));
        }
    }

    return ans;
}

void connect(const point &p1, const point &p2, multimap<ll, wall> &horizontal_walls, multimap<ll, wall> &vertical_walls) {
    if (p1.x == p2.x) {
        ll from = p1.y, to = p2.y;
        if (from > to) swap(from, to);
        vertical_walls.insert({p1.x, {from, to}});
    } else if (p1.y == p2.y) {
        ll from = p1.x, to = p2.x;
        if (from > to) swap(from, to);
        horizontal_walls.insert({p1.y, {from, to}});
    } else throw runtime_error("Invalid input - consecutive points cannot be connected.");
}

ll solve_part_two(const vector<point> &points) {
    multimap<ll, wall> horizontal_walls, vertical_walls;

    for (int i = 1; i < points.size(); i++)
        connect(points[i - 1], points[i], horizontal_walls, vertical_walls);
    connect(points[points.size() - 1], points[0], horizontal_walls, vertical_walls);

    ll ans = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            ll x1 = points[i].x, x2 = points[j].x, y1 = points[i].y, y2 = points[j].y;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            bool ok = true;

            if (x1 != x2) {
                const auto x_it_from = vertical_walls.upper_bound(x1), x_it_to = vertical_walls.lower_bound(x2);
                for (auto it = x_it_from; ok && it != x_it_to; ++it) {
                    if (y1 < it->second.to && it->second.from < y2) ok = false;
                }
            }

            if (!ok) continue;

            if (y1 != y2) {
                const auto y_it_from = horizontal_walls.upper_bound(y1), y_it_to = horizontal_walls.lower_bound(y2);
                for (auto it = y_it_from; ok && it != y_it_to; ++it) {
                    if (x1 < it->second.to && it->second.from < x2) ok = false;
                }
            }

            if (ok) ans = max(ans, (x2 - x1 + 1) * (y2 - y1 + 1));
        }
    }

    return ans;
}

int main() {
    ifstream in("Day 9.input.txt");

    vector<point> points;
    while (!in.eof()) {
        string line;
        getline(in, line);

        istringstream iss(line);
        ll x, y;
        iss >> x;
        iss.ignore(1, ',');
        iss >> y;

        points.push_back({x, y});
    }

    cout << "Part one: " << solve_part_one(points) << endl;
    cout << "Part two: " << solve_part_two(points) << endl;

    return 0;
}
