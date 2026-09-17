#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {

using Point = std::pair<int8_t, int8_t>;
using Shape = std::vector<Point>;

constexpr std::array<Point, 8> kKnightMoves{{
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
}};

Point transform(Point p, int symmetry) {
    const int x = p.first;
    const int y = p.second;
    switch (symmetry) {
        case 0: return {static_cast<int8_t>(x), static_cast<int8_t>(y)};
        case 1: return {static_cast<int8_t>(x), static_cast<int8_t>(-y)};
        case 2: return {static_cast<int8_t>(-x), static_cast<int8_t>(y)};
        case 3: return {static_cast<int8_t>(-x), static_cast<int8_t>(-y)};
        case 4: return {static_cast<int8_t>(y), static_cast<int8_t>(x)};
        case 5: return {static_cast<int8_t>(y), static_cast<int8_t>(-x)};
        case 6: return {static_cast<int8_t>(-y), static_cast<int8_t>(x)};
        default: return {static_cast<int8_t>(-y), static_cast<int8_t>(-x)};
    }
}

Shape normalize(Shape shape) {
    int min_x = shape.front().first;
    int min_y = shape.front().second;
    for (const auto& [x, y] : shape) {
        min_x = std::min(min_x, static_cast<int>(x));
        min_y = std::min(min_y, static_cast<int>(y));
    }
    for (auto& [x, y] : shape) {
        x = static_cast<int8_t>(static_cast<int>(x) - min_x);
        y = static_cast<int8_t>(static_cast<int>(y) - min_y);
    }
    std::sort(shape.begin(), shape.end());
    return shape;
}

std::string encode(const Shape& shape) {
    std::string key;
    key.reserve(shape.size() * 2);
    for (const auto& [x, y] : shape) {
        key.push_back(static_cast<char>(x));
        key.push_back(static_cast<char>(y));
    }
    return key;
}

std::pair<std::string, Shape> canonicalize(const Shape& shape) {
    std::string best_key;
    Shape best_shape;
    for (int symmetry = 0; symmetry < 8; ++symmetry) {
        Shape candidate;
        candidate.reserve(shape.size());
        for (const Point& point : shape) {
            candidate.push_back(transform(point, symmetry));
        }
        candidate = normalize(std::move(candidate));
        const std::string key = encode(candidate);
        if (symmetry == 0 || key < best_key) {
            best_key = key;
            best_shape = std::move(candidate);
        }
    }
    return {best_key, best_shape};
}

bool contains(const Shape& shape, Point point) {
    return std::find(shape.begin(), shape.end(), point) != shape.end();
}

std::vector<Shape> grow(const std::vector<Shape>& shapes) {
    std::unordered_set<std::string> seen;
    seen.reserve(shapes.size() * 12);
    std::vector<Shape> next;
    next.reserve(shapes.size() * 8);

    for (const Shape& shape : shapes) {
        for (const auto& [x, y] : shape) {
            for (const auto& [dx, dy] : kKnightMoves) {
                const Point added{
                    static_cast<int8_t>(static_cast<int>(x) + dx),
                    static_cast<int8_t>(static_cast<int>(y) + dy),
                };
                if (contains(shape, added)) continue;

                Shape candidate = shape;
                candidate.push_back(added);
                auto [key, canonical] = canonicalize(candidate);
                if (seen.insert(key).second) next.push_back(std::move(canonical));
            }
        }
    }
    return next;
}

bool is_knight_move(Point a, Point b) {
    const int dx = std::abs(static_cast<int>(a.first) - b.first);
    const int dy = std::abs(static_cast<int>(a.second) - b.second);
    return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
}

std::vector<uint16_t> adjacency(const Shape& shape) {
    std::vector<uint16_t> graph(shape.size(), 0);
    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = i + 1; j < shape.size(); ++j) {
            if (!is_knight_move(shape[i], shape[j])) continue;
            graph[i] |= static_cast<uint16_t>(1U << j);
            graph[j] |= static_cast<uint16_t>(1U << i);
        }
    }
    return graph;
}

bool bipartition_allows_path(const Shape& shape, bool cycle) {
    int even = 0;
    for (const auto& [x, y] : shape) even += ((x + y) & 1) == 0;
    const int odd = static_cast<int>(shape.size()) - even;
    return cycle ? even == odd : std::abs(even - odd) <= 1;
}

bool has_hamiltonian_path(const Shape& shape, const std::vector<uint16_t>& graph) {
    if (shape.size() == 1) return true;
    if (!bipartition_allows_path(shape, false)) return false;

    int leaves = 0;
    for (const uint16_t neighbors : graph) {
        const int degree = __builtin_popcount(static_cast<unsigned>(neighbors));
        if (degree == 0) return false;
        leaves += degree == 1;
    }
    if (leaves > 2) return false;

    const size_t state_count = size_t{1} << shape.size();
    std::vector<uint16_t> endpoints(state_count, 0);
    for (size_t v = 0; v < shape.size(); ++v) {
        endpoints[size_t{1} << v] = static_cast<uint16_t>(1U << v);
    }

    for (size_t mask = 1; mask < state_count; ++mask) {
        uint16_t ends = endpoints[mask];
        while (ends != 0) {
            const int last = __builtin_ctz(static_cast<unsigned>(ends));
            ends &= static_cast<uint16_t>(ends - 1);
            uint16_t available = graph[last] & static_cast<uint16_t>(~mask);
            while (available != 0) {
                const int next = __builtin_ctz(static_cast<unsigned>(available));
                available &= static_cast<uint16_t>(available - 1);
                endpoints[mask | (size_t{1} << next)] |= static_cast<uint16_t>(1U << next);
            }
        }
    }
    return endpoints.back() != 0;
}

bool has_hamiltonian_cycle(const Shape& shape, const std::vector<uint16_t>& graph) {
    const size_t n = shape.size();
    if (n < 4 || !bipartition_allows_path(shape, true)) return false;
    for (const uint16_t neighbors : graph) {
        if (__builtin_popcount(static_cast<unsigned>(neighbors)) < 2) return false;
    }

    const size_t state_count = size_t{1} << n;
    std::vector<uint16_t> endpoints(state_count, 0);
    endpoints[1] = 1;
    for (size_t mask = 1; mask < state_count; ++mask) {
        if ((mask & 1U) == 0) continue;
        uint16_t ends = endpoints[mask];
        while (ends != 0) {
            const int last = __builtin_ctz(static_cast<unsigned>(ends));
            ends &= static_cast<uint16_t>(ends - 1);
            uint16_t available = graph[last] & static_cast<uint16_t>(~mask);
            while (available != 0) {
                const int next = __builtin_ctz(static_cast<unsigned>(available));
                available &= static_cast<uint16_t>(available - 1);
                endpoints[mask | (size_t{1} << next)] |= static_cast<uint16_t>(1U << next);
            }
        }
    }
    return (endpoints.back() & graph[0]) != 0;
}

}  // namespace

int main() {
    constexpr int kMaximumSize = 8;
    static_assert(kMaximumSize <= 16, "uint16_t graph masks require at most 16 vertices");
    std::vector<uint64_t> all_counts;
    std::vector<uint64_t> open_counts;
    std::vector<uint64_t> closed_counts;
    std::vector<Shape> shapes{{Point{0, 0}}};

    for (int n = 1; n <= kMaximumSize; ++n) {
        uint64_t open = 0;
        uint64_t closed = 0;
        for (const Shape& shape : shapes) {
            const auto graph = adjacency(shape);
            open += has_hamiltonian_path(shape, graph);
            closed += has_hamiltonian_cycle(shape, graph);
        }
        all_counts.push_back(shapes.size());
        open_counts.push_back(open);
        closed_counts.push_back(closed);
        if (n != kMaximumSize) shapes = grow(shapes);
    }

    const auto print_sequence = [](const char* name, const std::vector<uint64_t>& values) {
        std::cout << name << "(1..8) = ";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i != 0) std::cout << ", ";
            std::cout << values[i];
        }
        std::cout << '\n';
    };

    print_sequence("A030446", all_counts);
    print_sequence("PO", open_counts);
    print_sequence("PC", closed_counts);
    return 0;
}
