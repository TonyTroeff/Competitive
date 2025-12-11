#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define llmax LONG_LONG_MAX
#define UNKNOWN (-1)

struct machine {
    uint16_t bits;
    uint16_t target_state;
    vector<uint16_t> changes;
    vector<int> joltage_requirements;
};

machine read_machine(const string &line) {
    istringstream iss(line);

    char buff;
    iss >> buff;

    if (buff != '[') throw runtime_error("State should be enclosed in [] brackets.");

    machine machine{};
    while (iss >> buff && buff != ']') {
        if (buff == '#') machine.target_state |= 1 << machine.bits;
        machine.bits++;
    }

    while (iss.ignore(1, ' ') && iss >> buff && buff == '(') {
        uint16_t change = 0;
        do {
            uint16_t pos;
            iss >> pos;

            change |= 1 << pos;
        } while (iss >> buff && buff == ',');

        if (buff != ')') throw runtime_error("Expected ')' after each wiring schematic.");

        machine.changes.push_back(change);
    }

    if (buff != '{') throw runtime_error("Expected '{' after wiring schematics.");

    do {
        int req;
        iss >> req;

        machine.joltage_requirements.push_back(req);
    } while (iss >> buff && buff == ',');

    if (buff != '}') throw runtime_error("Expected '}' at the end of the joltage requirements.");
    if (machine.bits != machine.joltage_requirements.size()) throw runtime_error("Number of bits and joltage requirements must be equal.");

    return machine;
}

int count_state_normalization_steps(const machine &machine) {
    queue<uint16_t> q;
    set<uint16_t> visited;

    q.push(0);
    visited.insert(0);

    int ops = 0;
    bool found = false;
    while (!found) {
        ops++;

        const int intermediate_states_count = static_cast<int>(q.size());
        for (int i = 0; i < intermediate_states_count; i++) {
            const uint16_t state = q.front();
            q.pop();

            for (const uint16_t &change: machine.changes) {
                const uint16_t next_state = state ^ change;

                if (next_state == machine.target_state) {
                    found = true;
                    break;
                }

                if (!visited.contains(next_state)) {
                    visited.insert(next_state);
                    q.push(next_state);
                }
            }

            if (found) break;
        }
    }

    return ops;
}

ll solve_part_one(const vector<machine> &machines) {
    ll ans = 0;

    for (const machine &machine: machines)
        ans += count_state_normalization_steps(machine);

    return ans;
}

int transform_into_upper_triangular_form(const int mat_height, const int mat_width, vector<vector<ll>> &aug_mat, vector<int> &pivot_col_by_row) {
    int rank = 0;

    for (int col = 0; col < mat_width && rank < mat_height; col++) {
        int pivot_row = UNKNOWN;
        for (int row = rank; row < mat_height; row++) {
            if (aug_mat[row][col] != 0) {
                pivot_row = row;
                break;
            }
        }

        if (pivot_row == UNKNOWN) continue;

        swap(aug_mat[rank], aug_mat[pivot_row]);
        pivot_col_by_row[rank] = col;

        // Eliminate this column from all other rows
        for (int row = 0; row < mat_height; row++) {
            if (row == rank || aug_mat[row][col] == 0) continue;

            const ll f1 = aug_mat[rank][col], f2 = aug_mat[row][col];
            for (int k = 0; k <= mat_width; k++)
                aug_mat[row][k] = aug_mat[row][k] * f1 - aug_mat[rank][k] * f2;

            // Reduce by GCD
            ll row_gcd = abs(aug_mat[row][0]);
            for (int k = 1; k <= mat_width && row_gcd != 1; k++)
                row_gcd = gcd(row_gcd, abs(aug_mat[row][k]));

            if (row_gcd > 1) {
                for (int k = 0; k <= mat_width; k++) aug_mat[row][k] /= row_gcd;
            }
        }

        rank++;
    }

    return rank;
}

vector<int> find_free_variables(const int rank, const int mat_width, const vector<int> &pivot_col_by_rank) {
    vector<int> free_variables;
    vector is_pivot_col(mat_width, false);
    for (int r = 0; r < rank; r++) is_pivot_col[pivot_col_by_rank[r]] = true;
    for (int c = 0; c < mat_width; c++) {
        if (!is_pivot_col[c]) free_variables.push_back(c);
    }

    return free_variables;
}

vector<ll> calculate_free_variable_limits(const machine &machine, const vector<int>& free_vars) {
    vector free_var_lims(free_vars.size(), llmax);
    for (int v = 0; v < free_vars.size(); v++) {
        const int var_col = free_vars[v];
        for (int i = 0; i < machine.bits; i++) {
            if (machine.changes[var_col] & (1 << i))
                free_var_lims[v] = min(free_var_lims[v], static_cast<ll>(machine.joltage_requirements[i]));
        }
    }

    return free_var_lims;
}

// Solves a system of linear equations Ax = b over non-negative integers, minimizing sum(x).
// Uses Gaussian elimination to reduce the system, then enumerates free variables.
ll solve_ilp(const machine &machine) {
    const int mat_height = machine.bits;
    const int mat_width = static_cast<int>(machine.changes.size());

    // Augmented matrix: [A | b]
    vector aug_mat(mat_height, vector<ll>(mat_width + 1));
    for (int i = 0; i < mat_height; i++) {
        for (int j = 0; j < mat_width; j++)
            aug_mat[i][j] = machine.changes[j] & (1 << i) ? 1 : 0;
        aug_mat[i][mat_width] = machine.joltage_requirements[i];
    }

    vector pivot_col_by_row(mat_height, UNKNOWN);
    const int rank = transform_into_upper_triangular_form(mat_height, mat_width, aug_mat, pivot_col_by_row);

    const vector<int> free_vars = find_free_variables(rank, mat_width, pivot_col_by_row);
    vector<long long> free_var_lims = calculate_free_variable_limits(machine, free_vars);

    ll min_sum = llmax;
    vector<ll> free_var_vals(free_vars.size());

    function<void(int, ll)> enumerate;
    enumerate = [&](const int idx, const ll free_sum) -> void {
        if (free_sum >= min_sum) return;

        if (idx == free_vars.size()) {
            ll total_sum = free_sum;

            for (int r = 0; r < rank; r++) {
                ll rhs = aug_mat[r][mat_width];
                for (int v = 0; v < free_vars.size(); v++) {
                    const int var_col = free_vars[v];
                    rhs -= aug_mat[r][var_col] * free_var_vals[v];
                }

                const int pivot_col = pivot_col_by_row[r];
                const ll divisor = aug_mat[r][pivot_col];
                if (rhs % divisor != 0) return;

                const ll pivot_val = rhs / divisor;
                if (pivot_val < 0) return;

                total_sum += pivot_val;
                if (total_sum >= min_sum) return;
            }

            min_sum = total_sum;
        } else {
            for (ll v = 0; v <= free_var_lims[idx] && free_sum + v < min_sum; v++) {
                free_var_vals[idx] = v;
                enumerate(idx + 1, free_sum + v);
            }
        }
    };

    enumerate(0, 0);

    if (min_sum == llmax) throw runtime_error("No feasible solution found.");
    return min_sum;
}

ll solve_part_two(const vector<machine> &machines) {
    ll ans = 0;

    for (const machine &machine: machines)
        ans += solve_ilp(machine);

    return ans;
}

int main() {
    ifstream in("Day 10.input.txt");

    vector<machine> machines;
    while (!in.eof()) {
        string line;
        getline(in, line);

        machine machine = read_machine(line);
        machines.push_back(machine);
    }

    cout << "Part one: " << solve_part_one(machines) << endl;
    cout << "Part two: " << solve_part_two(machines) << endl;
}
