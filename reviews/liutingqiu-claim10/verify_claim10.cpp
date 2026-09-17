#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Point {
    int x;
    int y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point &other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
};

static constexpr std::array<Point, 4> STEPS{{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
}};

static std::uint64_t packed(const Point &p) {
    return static_cast<std::uint64_t>(p.x + 32) |
           (static_cast<std::uint64_t>(p.y + 32) << 7);
}

static std::string encode(const std::vector<Point> &shape) {
    std::string key;
    key.reserve(shape.size() * 2);
    for (const Point &p : shape) {
        key.push_back(static_cast<char>(p.x + 64));
        key.push_back(static_cast<char>(p.y + 64));
    }
    return key;
}

static std::vector<Point> decode(const std::string &key) {
    std::vector<Point> shape;
    shape.reserve(key.size() / 2);
    for (std::size_t i = 0; i < key.size(); i += 2) {
        shape.push_back({
            static_cast<unsigned char>(key[i]) - 64,
            static_cast<unsigned char>(key[i + 1]) - 64
        });
    }
    return shape;
}

static Point transform(Point p, int symmetry) {
    switch (symmetry) {
        case 0: return {p.x, p.y};
        case 1: return {p.x, -p.y};
        case 2: return {-p.x, p.y};
        case 3: return {-p.x, -p.y};
        case 4: return {p.y, p.x};
        case 5: return {p.y, -p.x};
        case 6: return {-p.y, p.x};
        default: return {-p.y, -p.x};
    }
}

static std::string canonical(const std::vector<Point> &shape) {
    std::string best;
    bool have_best = false;
    for (int symmetry = 0; symmetry < 8; ++symmetry) {
        std::vector<Point> candidate;
        candidate.reserve(shape.size());
        int min_x = 1000;
        int min_y = 1000;
        for (Point p : shape) {
            p = transform(p, symmetry);
            min_x = std::min(min_x, p.x);
            min_y = std::min(min_y, p.y);
            candidate.push_back(p);
        }
        for (Point &p : candidate) {
            p.x -= min_x;
            p.y -= min_y;
        }
        std::sort(candidate.begin(), candidate.end());
        std::string key = encode(candidate);
        if (!have_best || key < best) {
            best = std::move(key);
            have_best = true;
        }
    }
    return best;
}

static std::vector<std::uint32_t> cell_adjacency(const std::vector<Point> &shape) {
    std::unordered_map<std::uint64_t, int> index;
    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        index[packed(shape[i])] = i;
    }
    std::vector<std::uint32_t> adjacency(shape.size(), 0);
    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (Point step : STEPS) {
            Point next{shape[i].x + step.x, shape[i].y + step.y};
            auto found = index.find(packed(next));
            if (found != index.end()) {
                adjacency[i] |= std::uint32_t{1} << found->second;
            }
        }
    }
    return adjacency;
}

static int rank_gf2(std::vector<std::uint32_t> rows, int columns) {
    int rank = 0;
    for (int column = 0; column < columns; ++column) {
        int pivot = rank;
        while (pivot < static_cast<int>(rows.size()) &&
               (rows[pivot] & (std::uint32_t{1} << column)) == 0) {
            ++pivot;
        }
        if (pivot == static_cast<int>(rows.size())) continue;
        std::swap(rows[rank], rows[pivot]);
        for (int row = rank + 1; row < static_cast<int>(rows.size()); ++row) {
            if (rows[row] & (std::uint32_t{1} << column)) rows[row] ^= rows[rank];
        }
        ++rank;
    }
    return rank;
}

static std::vector<std::uint32_t> laplacian_gf2(
    const std::vector<std::uint32_t> &adjacency
) {
    std::vector<std::uint32_t> rows = adjacency;
    for (int i = 0; i < static_cast<int>(adjacency.size()); ++i) {
        if (__builtin_popcount(adjacency[i]) & 1) rows[i] |= std::uint32_t{1} << i;
    }
    return rows;
}

static int laplacian_nullity(const std::vector<std::uint32_t> &adjacency) {
    std::vector<std::uint32_t> rows = laplacian_gf2(adjacency);
    int n = static_cast<int>(rows.size());
    return n - rank_gf2(std::move(rows), n);
}

static bool spanning_tree_is_odd(const std::vector<std::uint32_t> &adjacency) {
    int n = static_cast<int>(adjacency.size());
    if (n == 1) return true;
    std::vector<std::uint32_t> laplacian = laplacian_gf2(adjacency);
    std::uint32_t mask = (std::uint32_t{1} << (n - 1)) - 1;
    std::vector<std::uint32_t> cofactor;
    cofactor.reserve(n - 1);
    for (int row = 0; row < n - 1; ++row) cofactor.push_back(laplacian[row] & mask);
    return rank_gf2(std::move(cofactor), n - 1) == n - 1;
}

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n), rank_(n, 0) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int value) {
        if (parent_[value] != value) parent_[value] = find(parent_[value]);
        return parent_[value];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank_[a] < rank_[b]) std::swap(a, b);
        parent_[b] = a;
        if (rank_[a] == rank_[b]) ++rank_[a];
    }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
};

enum Corner { NW = 0, NE = 1, SE = 2, SW = 3 };

static int mirror_loops_corner_graph(const std::vector<Point> &shape) {
    std::unordered_map<std::uint64_t, int> index;
    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        index[packed(shape[i])] = i;
    }
    DisjointSet arcs(static_cast<int>(shape.size()) * 4);
    auto arc = [](int cell, Corner corner) { return cell * 4 + static_cast<int>(corner); };
    auto neighbor = [&](int cell, int side) -> int {
        Point next{shape[cell].x + STEPS[side].x, shape[cell].y + STEPS[side].y};
        auto found = index.find(packed(next));
        return found == index.end() ? -1 : found->second;
    };

    for (int cell = 0; cell < static_cast<int>(shape.size()); ++cell) {
        int north = neighbor(cell, 0);
        int east = neighbor(cell, 1);
        int south = neighbor(cell, 2);
        int west = neighbor(cell, 3);
        if (north >= 0) {
            arcs.unite(arc(cell, NW), arc(north, SE));
            arcs.unite(arc(cell, NE), arc(north, SW));
        } else {
            arcs.unite(arc(cell, NW), arc(cell, NE));
        }
        if (east >= 0) {
            arcs.unite(arc(cell, NE), arc(east, SW));
            arcs.unite(arc(cell, SE), arc(east, NW));
        } else {
            arcs.unite(arc(cell, NE), arc(cell, SE));
        }
        if (south >= 0) {
            arcs.unite(arc(cell, SE), arc(south, NW));
            arcs.unite(arc(cell, SW), arc(south, NE));
        } else {
            arcs.unite(arc(cell, SE), arc(cell, SW));
        }
        if (west >= 0) {
            arcs.unite(arc(cell, NW), arc(west, SE));
            arcs.unite(arc(cell, SW), arc(west, NE));
        } else {
            arcs.unite(arc(cell, SW), arc(cell, NW));
        }
    }

    std::unordered_set<int> components;
    for (int node = 0; node < static_cast<int>(shape.size()) * 4; ++node) {
        components.insert(arcs.find(node));
    }
    return static_cast<int>(components.size());
}

struct RayState {
    int cell;
    int side;
    int dx;
    int dy;
};

static std::uint64_t ray_key(int cell, int side, int dx, int dy) {
    return static_cast<std::uint64_t>(cell) |
           (static_cast<std::uint64_t>(side) << 10) |
           (static_cast<std::uint64_t>(dx > 0) << 13) |
           (static_cast<std::uint64_t>(dy > 0) << 14);
}

static int mirror_loops_directed_rays(const std::vector<Point> &shape) {
    std::unordered_map<std::uint64_t, int> cell_index;
    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        cell_index[packed(shape[i])] = i;
    }

    std::vector<RayState> states;
    std::unordered_map<std::uint64_t, int> state_index;
    for (int cell = 0; cell < static_cast<int>(shape.size()); ++cell) {
        for (int tangent : {-1, 1}) {
            states.push_back({cell, 0, tangent, -1});
            states.push_back({cell, 1, -1, tangent});
            states.push_back({cell, 2, tangent, 1});
            states.push_back({cell, 3, 1, tangent});
        }
    }
    for (int i = 0; i < static_cast<int>(states.size()); ++i) {
        const RayState &s = states[i];
        state_index[ray_key(s.cell, s.side, s.dx, s.dy)] = i;
    }

    std::vector<int> transition(states.size(), -1);
    for (int i = 0; i < static_cast<int>(states.size()); ++i) {
        RayState next = states[i];
        int exit_side;
        if (next.side == 0 || next.side == 2) {
            exit_side = next.dx > 0 ? 1 : 3;
        } else {
            exit_side = next.dy > 0 ? 0 : 2;
        }

        Point adjacent_cell{
            shape[next.cell].x + STEPS[exit_side].x,
            shape[next.cell].y + STEPS[exit_side].y
        };
        auto found = cell_index.find(packed(adjacent_cell));
        if (found != cell_index.end()) {
            next.cell = found->second;
            next.side = (exit_side + 2) % 4;
        } else {
            next.side = exit_side;
            if (exit_side == 0 || exit_side == 2) next.dy = -next.dy;
            else next.dx = -next.dx;
        }
        auto destination = state_index.find(ray_key(next.cell, next.side, next.dx, next.dy));
        if (destination == state_index.end()) {
            std::cerr << "invalid directed-ray transition\n";
            std::exit(2);
        }
        transition[i] = destination->second;
    }

    std::vector<bool> visited(states.size(), false);
    int directed_cycles = 0;
    for (int start = 0; start < static_cast<int>(states.size()); ++start) {
        if (visited[start]) continue;
        ++directed_cycles;
        int current = start;
        do {
            visited[current] = true;
            current = transition[current];
        } while (!visited[current]);
        if (current != start) {
            std::cerr << "directed-ray map is not a permutation\n";
            std::exit(2);
        }
    }
    if (directed_cycles & 1) {
        std::cerr << "odd number of directed mirror trajectories\n";
        std::exit(2);
    }
    return directed_cycles / 2;
}

static bool brute_spanning_tree_parity(const std::vector<std::uint32_t> &adjacency) {
    int n = static_cast<int>(adjacency.size());
    if (n == 1) return true;
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacency[i] & (std::uint32_t{1} << j)) edges.emplace_back(i, j);
        }
    }
    bool parity = false;
    std::uint64_t combinations = std::uint64_t{1} << edges.size();
    for (std::uint64_t mask = 0; mask < combinations; ++mask) {
        if (__builtin_popcountll(mask) != n - 1) continue;
        DisjointSet forest(n);
        for (int edge = 0; edge < static_cast<int>(edges.size()); ++edge) {
            if (mask & (std::uint64_t{1} << edge)) {
                forest.unite(edges[edge].first, edges[edge].second);
            }
        }
        bool connected = true;
        for (int vertex = 1; vertex < n; ++vertex) {
            connected &= forest.find(vertex) == forest.find(0);
        }
        if (connected) parity = !parity;
    }
    return parity;
}

static std::vector<Point> rectangle(int width, int height) {
    std::vector<Point> shape;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) shape.push_back({x, y});
    }
    return shape;
}

int main() {
    constexpr int limit = 12;
    constexpr int part_a_limit = 11;
    constexpr int independent_limit = 7;

    std::unordered_set<std::string> current{canonical({{0, 0}})};
    std::array<std::uint64_t, limit + 1> free_counts{};
    std::array<std::uint64_t, limit + 1> odd_tree_counts{};
    std::array<std::array<std::uint64_t, 16>, part_a_limit + 1> loop_distribution{};
    std::array<std::uint64_t, part_a_limit + 1> mismatches{};
    int maximum_loop_count = 0;
    bool independent_ok = true;

    for (int n = 1; n <= limit; ++n) {
        free_counts[n] = current.size();
        for (const std::string &key : current) {
            std::vector<Point> shape = decode(key);
            std::vector<std::uint32_t> adjacency = cell_adjacency(shape);
            bool odd = spanning_tree_is_odd(adjacency);
            odd_tree_counts[n] += odd;

            if (n <= part_a_limit) {
                int loops = mirror_loops_corner_graph(shape);
                int nullity = laplacian_nullity(adjacency);
                if (loops >= static_cast<int>(loop_distribution[n].size())) {
                    std::cerr << "unexpectedly large mirror loop count\n";
                    return 2;
                }
                ++loop_distribution[n][loops];
                mismatches[n] += loops != nullity;
                maximum_loop_count = std::max(maximum_loop_count, loops);
            }
            if (n <= independent_limit) {
                independent_ok &= mirror_loops_corner_graph(shape) ==
                                  mirror_loops_directed_rays(shape);
                independent_ok &= odd == brute_spanning_tree_parity(adjacency);
            }
        }

        if (n == limit) break;
        std::unordered_set<std::string> next_shapes;
        next_shapes.reserve(current.size() * 4);
        for (const std::string &key : current) {
            std::vector<Point> shape = decode(key);
            std::unordered_set<std::uint64_t> occupied;
            std::unordered_map<std::uint64_t, Point> boundary;
            for (const Point &p : shape) occupied.insert(packed(p));
            for (const Point &p : shape) {
                for (const Point &step : STEPS) {
                    Point candidate{p.x + step.x, p.y + step.y};
                    std::uint64_t code = packed(candidate);
                    if (!occupied.count(code)) boundary.emplace(code, candidate);
                }
            }
            for (const auto &entry : boundary) {
                shape.push_back(entry.second);
                next_shapes.insert(canonical(shape));
                shape.pop_back();
            }
        }
        current = std::move(next_shapes);
    }

    for (int width = 1; width <= 8; ++width) {
        for (int height = 1; height <= 8; ++height) {
            independent_ok &= mirror_loops_corner_graph(rectangle(width, height)) ==
                              std::gcd(width, height);
        }
    }

    std::cout << "free_polyominoes(1..12) = ";
    for (int n = 1; n <= limit; ++n) {
        if (n > 1) std::cout << ", ";
        std::cout << free_counts[n];
    }
    std::cout << "\nodd_spanning_tree_counts(1..12) = ";
    for (int n = 1; n <= limit; ++n) {
        if (n > 1) std::cout << ", ";
        std::cout << odd_tree_counts[n];
    }
    std::cout << "\n";

    std::uint64_t total_shapes = 0;
    std::uint64_t total_mismatches = 0;
    for (int n = 1; n <= part_a_limit; ++n) {
        total_shapes += free_counts[n];
        total_mismatches += mismatches[n];
        std::cout << "n=" << n << " shapes=" << free_counts[n]
                  << " loop_distribution=";
        for (int loops = 1; loops <= maximum_loop_count; ++loops) {
            if (loops > 1) std::cout << ",";
            std::cout << loops << ":" << loop_distribution[n][loops];
        }
        std::cout << " mismatches=" << mismatches[n] << "\n";
    }
    std::cout << "part_a_total_shapes=" << total_shapes
              << " total_mismatches=" << total_mismatches
              << " maximum_loop_count=" << maximum_loop_count << "\n";
    std::cout << "independent_directed_ray_tree_subset_checks_through_7="
              << (independent_ok ? "PASS" : "FAIL") << "\n";

    bool passed = independent_ok && total_mismatches == 0;
    std::cout << "verdict=" << (passed ? "reproduces minimum" : "cross-check failed") << "\n";
    return passed ? 0 : 1;
}
