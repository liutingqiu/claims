#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Vertex {
    int x;
    int y;
    int z;

    bool operator==(const Vertex &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator<(const Vertex &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

using ShapeSet = std::unordered_set<std::string>;
using Neighbors = std::function<std::vector<Vertex>(const Vertex &)>;
using Canonicalizer = std::function<std::string(const std::vector<Vertex> &)>;

static constexpr std::array<std::array<int, 3>, 6> PERMUTATIONS{{
    {{0, 1, 2}}, {{0, 2, 1}}, {{1, 0, 2}},
    {{1, 2, 0}}, {{2, 0, 1}}, {{2, 1, 0}}
}};

static std::uint64_t packed(const Vertex &v) {
    constexpr int offset = 32;
    return static_cast<std::uint64_t>(v.x + offset) |
           (static_cast<std::uint64_t>(v.y + offset) << 7) |
           (static_cast<std::uint64_t>(v.z + offset) << 14);
}

static std::string encode(const std::vector<Vertex> &vertices) {
    std::string key;
    key.reserve(vertices.size() * 3);
    for (const Vertex &v : vertices) {
        key.push_back(static_cast<char>(v.x + 64));
        key.push_back(static_cast<char>(v.y + 64));
        key.push_back(static_cast<char>(v.z + 64));
    }
    return key;
}

static std::vector<Vertex> decode(const std::string &key) {
    std::vector<Vertex> vertices;
    vertices.reserve(key.size() / 3);
    for (std::size_t i = 0; i < key.size(); i += 3) {
        vertices.push_back({
            static_cast<unsigned char>(key[i]) - 64,
            static_cast<unsigned char>(key[i + 1]) - 64,
            static_cast<unsigned char>(key[i + 2]) - 64
        });
    }
    return vertices;
}

static Vertex permute(const Vertex &v, const std::array<int, 3> &p) {
    int values[3] = {v.x, v.y, v.z};
    return {values[p[0]], values[p[1]], values[p[2]]};
}

static std::string canonical_triangular(const std::vector<Vertex> &vertices) {
    std::string best;
    bool have_best = false;
    for (const auto &p : PERMUTATIONS) {
        for (int sign : {1, -1}) {
            std::vector<Vertex> transformed;
            transformed.reserve(vertices.size());
            for (const Vertex &v : vertices) {
                Vertex w = permute(v, p);
                transformed.push_back({sign * w.x, sign * w.y, sign * w.z});
            }
            Vertex base = *std::min_element(transformed.begin(), transformed.end());
            for (Vertex &w : transformed) {
                w.x -= base.x;
                w.y -= base.y;
                w.z -= base.z;
            }
            std::sort(transformed.begin(), transformed.end());
            std::string key = encode(transformed);
            if (!have_best || key < best) {
                best = std::move(key);
                have_best = true;
            }
        }
    }
    return best;
}

static std::string canonical_honeycomb(const std::vector<Vertex> &vertices) {
    if (vertices.size() == 1) {
        return encode({{0, 0, 0}});
    }
    std::string best;
    bool have_best = false;
    for (const auto &p : PERMUTATIONS) {
        for (bool swap_sublattices : {false, true}) {
            std::vector<Vertex> transformed;
            transformed.reserve(vertices.size());
            for (const Vertex &v : vertices) {
                Vertex w = permute(v, p);
                if (swap_sublattices) {
                    w = {1 - w.x, -w.y, -w.z};
                }
                transformed.push_back(w);
            }
            bool found_base = false;
            Vertex base{};
            for (const Vertex &w : transformed) {
                if (w.x + w.y + w.z == 0 && (!found_base || w < base)) {
                    base = w;
                    found_base = true;
                }
            }
            if (!found_base) {
                std::cerr << "honeycomb shape has no sum-0 vertex\n";
                std::exit(2);
            }
            for (Vertex &w : transformed) {
                w.x -= base.x;
                w.y -= base.y;
                w.z -= base.z;
            }
            std::sort(transformed.begin(), transformed.end());
            std::string key = encode(transformed);
            if (!have_best || key < best) {
                best = std::move(key);
                have_best = true;
            }
        }
    }
    return best;
}

static std::vector<Vertex> triangular_neighbors(const Vertex &v) {
    static constexpr std::array<Vertex, 6> steps{{
        {1, -1, 0}, {1, 0, -1}, {0, 1, -1},
        {-1, 1, 0}, {-1, 0, 1}, {0, -1, 1}
    }};
    std::vector<Vertex> result;
    result.reserve(6);
    for (const Vertex &step : steps) {
        result.push_back({v.x + step.x, v.y + step.y, v.z + step.z});
    }
    return result;
}

static std::vector<Vertex> honeycomb_neighbors(const Vertex &v) {
    int sum = v.x + v.y + v.z;
    if (sum == 0) {
        return {{v.x + 1, v.y, v.z}, {v.x, v.y + 1, v.z}, {v.x, v.y, v.z + 1}};
    }
    if (sum == 1) {
        return {{v.x - 1, v.y, v.z}, {v.x, v.y - 1, v.z}, {v.x, v.y, v.z - 1}};
    }
    std::cerr << "invalid honeycomb vertex\n";
    std::exit(2);
}

static bool adjacent(const Vertex &a, const Vertex &b, const Neighbors &neighbors) {
    for (const Vertex &candidate : neighbors(a)) {
        if (candidate == b) return true;
    }
    return false;
}

struct WalkCounts {
    std::vector<ShapeSet> paths;
    std::vector<ShapeSet> cycles;
};

static WalkCounts enumerate_walk_vertex_sets(
    int limit,
    const Vertex &first,
    int minimum_cycle,
    const Neighbors &neighbors,
    const Canonicalizer &canonicalize
) {
    WalkCounts counts{std::vector<ShapeSet>(limit + 1), std::vector<ShapeSet>(limit + 1)};
    std::vector<Vertex> path{{0, 0, 0}};
    std::unordered_set<std::uint64_t> occupied{packed(path.front())};
    counts.paths[1].insert(canonicalize(path));

    path.push_back(first);
    occupied.insert(packed(first));

    std::function<void()> visit = [&]() {
        int n = static_cast<int>(path.size());
        counts.paths[n].insert(canonicalize(path));
        if (n >= minimum_cycle && adjacent(path.back(), path.front(), neighbors)) {
            counts.cycles[n].insert(canonicalize(path));
        }
        if (n == limit) return;

        for (const Vertex &next : neighbors(path.back())) {
            std::uint64_t code = packed(next);
            if (occupied.count(code)) continue;
            occupied.insert(code);
            path.push_back(next);
            visit();
            path.pop_back();
            occupied.erase(code);
        }
    };
    visit();
    return counts;
}

struct ShapeGrowthResult {
    std::vector<std::uint64_t> free_counts;
    std::vector<std::uint64_t> dp_path_counts;
    std::vector<std::uint64_t> dp_cycle_counts;
};

static std::pair<bool, bool> hamiltonian_dp(
    const std::vector<Vertex> &vertices,
    const Neighbors &neighbors
) {
    int n = static_cast<int>(vertices.size());
    std::unordered_map<std::uint64_t, int> index;
    for (int i = 0; i < n; ++i) index[packed(vertices[i])] = i;

    std::vector<std::uint32_t> adjacency(n, 0);
    for (int i = 0; i < n; ++i) {
        for (const Vertex &next : neighbors(vertices[i])) {
            auto found = index.find(packed(next));
            if (found != index.end()) adjacency[i] |= std::uint32_t{1} << found->second;
        }
    }

    std::size_t states = std::size_t{1} << n;
    std::vector<std::uint32_t> reachable(states, 0);
    for (int i = 0; i < n; ++i) reachable[std::size_t{1} << i] |= std::uint32_t{1} << i;
    for (std::size_t mask = 1; mask < states; ++mask) {
        std::uint32_t endpoints = reachable[mask];
        while (endpoints) {
            int endpoint = __builtin_ctz(endpoints);
            endpoints &= endpoints - 1;
            std::uint32_t nexts = adjacency[endpoint] & ~static_cast<std::uint32_t>(mask);
            while (nexts) {
                int next = __builtin_ctz(nexts);
                nexts &= nexts - 1;
                reachable[mask | (std::size_t{1} << next)] |= std::uint32_t{1} << next;
            }
        }
    }
    bool has_path = reachable.back() != 0;

    bool has_cycle = false;
    if (n >= 3) {
        std::fill(reachable.begin(), reachable.end(), 0);
        reachable[1] = 1;
        for (std::size_t mask = 1; mask < states; ++mask) {
            if ((mask & 1) == 0) continue;
            std::uint32_t endpoints = reachable[mask];
            while (endpoints) {
                int endpoint = __builtin_ctz(endpoints);
                endpoints &= endpoints - 1;
                std::uint32_t nexts = adjacency[endpoint] & ~static_cast<std::uint32_t>(mask);
                while (nexts) {
                    int next = __builtin_ctz(nexts);
                    nexts &= nexts - 1;
                    reachable[mask | (std::size_t{1} << next)] |= std::uint32_t{1} << next;
                }
            }
        }
        has_cycle = (reachable.back() & adjacency[0]) != 0;
    }
    return {has_path, has_cycle};
}

static ShapeGrowthResult grow_all_shapes(
    int limit,
    int dp_limit,
    const Neighbors &neighbors,
    const Canonicalizer &canonicalize
) {
    ShapeGrowthResult result{
        std::vector<std::uint64_t>(limit + 1, 0),
        std::vector<std::uint64_t>(dp_limit + 1, 0),
        std::vector<std::uint64_t>(dp_limit + 1, 0)
    };
    ShapeSet current;
    current.insert(canonicalize({{0, 0, 0}}));

    for (int n = 1; n <= limit; ++n) {
        result.free_counts[n] = current.size();
        if (n <= dp_limit) {
            for (const std::string &key : current) {
                auto [has_path, has_cycle] = hamiltonian_dp(decode(key), neighbors);
                result.dp_path_counts[n] += has_path;
                result.dp_cycle_counts[n] += has_cycle;
            }
        }
        if (n == limit) break;

        ShapeSet next_shapes;
        next_shapes.reserve(current.size() * 4);
        for (const std::string &key : current) {
            std::vector<Vertex> shape = decode(key);
            std::unordered_set<std::uint64_t> occupied;
            std::unordered_map<std::uint64_t, Vertex> boundary;
            for (const Vertex &v : shape) occupied.insert(packed(v));
            for (const Vertex &v : shape) {
                for (const Vertex &candidate : neighbors(v)) {
                    std::uint64_t code = packed(candidate);
                    if (!occupied.count(code)) boundary.emplace(code, candidate);
                }
            }
            for (const auto &entry : boundary) {
                shape.push_back(entry.second);
                next_shapes.insert(canonicalize(shape));
                shape.pop_back();
            }
        }
        current = std::move(next_shapes);
    }
    return result;
}

static void print_sequence(const std::string &name, const std::vector<std::uint64_t> &values,
                           int first, int last) {
    std::cout << name << "(" << first << ".." << last << ") = ";
    for (int n = first; n <= last; ++n) {
        if (n != first) std::cout << ", ";
        std::cout << values[n];
    }
    std::cout << "\n";
}

static std::vector<std::uint64_t> set_sizes(const std::vector<ShapeSet> &sets) {
    std::vector<std::uint64_t> result(sets.size(), 0);
    for (std::size_t i = 0; i < sets.size(); ++i) result[i] = sets[i].size();
    return result;
}

int main() {
    const int p6_limit = 12;
    const int p3_limit = 18;
    const int side_polyhex_limit = 12;
    const int side_polyiamond_limit = 15;
    const int independent_dp_limit = 8;

    WalkCounts triangular_walks = enumerate_walk_vertex_sets(
        p6_limit, {1, -1, 0}, 3, triangular_neighbors, canonical_triangular);
    WalkCounts honeycomb_walks = enumerate_walk_vertex_sets(
        p3_limit, {1, 0, 0}, 6, honeycomb_neighbors, canonical_honeycomb);

    ShapeGrowthResult polyhexes = grow_all_shapes(
        side_polyhex_limit, independent_dp_limit,
        triangular_neighbors, canonical_triangular);
    ShapeGrowthResult polyiamonds = grow_all_shapes(
        side_polyiamond_limit, independent_dp_limit,
        honeycomb_neighbors, canonical_honeycomb);

    std::vector<std::uint64_t> p6 = set_sizes(triangular_walks.paths);
    std::vector<std::uint64_t> c6 = set_sizes(triangular_walks.cycles);
    std::vector<std::uint64_t> p3 = set_sizes(honeycomb_walks.paths);
    std::vector<std::uint64_t> c3 = set_sizes(honeycomb_walks.cycles);

    bool independent_ok = true;
    for (int n = 1; n <= independent_dp_limit; ++n) {
        independent_ok &= p6[n] == polyhexes.dp_path_counts[n];
        independent_ok &= c6[n] == polyhexes.dp_cycle_counts[n];
        independent_ok &= p3[n] == polyiamonds.dp_path_counts[n];
        independent_ok &= c3[n] == polyiamonds.dp_cycle_counts[n];
    }

    print_sequence("P6", p6, 1, p6_limit);
    print_sequence("C6", c6, 1, p6_limit);
    print_sequence("P3", p3, 1, p3_limit);
    print_sequence("C3", c3, 1, p3_limit);
    print_sequence("free_polyhexes", polyhexes.free_counts, 1, side_polyhex_limit);
    print_sequence("free_polyiamonds", polyiamonds.free_counts, 1, side_polyiamond_limit);
    std::cout << "independent_shape_dp_through_8=" << (independent_ok ? "PASS" : "FAIL") << "\n";
    std::cout << "verdict=" << (independent_ok ? "reproduces minimum" : "cross-check failed") << "\n";
    return independent_ok ? 0 : 1;
}
