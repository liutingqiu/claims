#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_N = 30, MAX_VERTICES = 38, GRID = 81, OFFSET = 40 };

typedef struct {
    int x;
    int y;
    int z;
} Vertex;

static Vertex path_vertices[MAX_N];
static bool occupied[GRID][GRID][GRID];
static uint64_t rooted_polygons[MAX_N + 1];
static uint64_t chorded_polygons[MAX_N + 1];
static int max_cycles[MAX_N + 1];

static uint64_t ham_adj[MAX_VERTICES];
static int ham_n;
static int ham_start;
static int ham_stop_after;

static bool same_vertex(Vertex a, Vertex b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static bool adjacent(Vertex a, Vertex b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    int dz = abs(a.z - b.z);
    return dx + dy + dz == 1;
}

static int neighbors(Vertex v, Vertex out[3]) {
    int sum = v.x + v.y + v.z;
    if (sum == 0) {
        out[0] = (Vertex){v.x + 1, v.y, v.z};
        out[1] = (Vertex){v.x, v.y + 1, v.z};
        out[2] = (Vertex){v.x, v.y, v.z + 1};
    } else if (sum == 1) {
        out[0] = (Vertex){v.x - 1, v.y, v.z};
        out[1] = (Vertex){v.x, v.y - 1, v.z};
        out[2] = (Vertex){v.x, v.y, v.z - 1};
    } else {
        fprintf(stderr, "invalid lattice vertex (%d,%d,%d)\n", v.x, v.y, v.z);
        exit(2);
    }
    return 3;
}

static bool in_grid(Vertex v) {
    return v.x >= -OFFSET && v.x < GRID - OFFSET &&
           v.y >= -OFFSET && v.y < GRID - OFFSET &&
           v.z >= -OFFSET && v.z < GRID - OFFSET;
}

static bool is_occupied(Vertex v) {
    return occupied[v.x + OFFSET][v.y + OFFSET][v.z + OFFSET];
}

static void set_occupied(Vertex v, bool value) {
    occupied[v.x + OFFSET][v.y + OFFSET][v.z + OFFSET] = value;
}

static int lattice_distance_lower_bound(Vertex v) {
    return abs(v.x) + abs(v.y) + abs(v.z);
}

static int popcount64(uint64_t value) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_popcountll(value);
#else
    int count = 0;
    while (value) {
        value &= value - 1;
        ++count;
    }
    return count;
#endif
}

static int hamiltonian_dfs(int current, uint64_t visited, int depth) {
    if (depth == ham_n) {
        return (ham_adj[current] & (UINT64_C(1) << ham_start)) != 0;
    }

    uint64_t candidates = ham_adj[current] & ~visited;
    candidates &= ~(UINT64_C(1) << ham_start);
    int total = 0;

    while (candidates) {
        uint64_t bit = candidates & (~candidates + 1);
        candidates ^= bit;
#if defined(__GNUC__) || defined(__clang__)
        int next = __builtin_ctzll(bit);
#else
        int next = 0;
        while ((bit >> next) != 1) {
            ++next;
        }
#endif
        total += hamiltonian_dfs(next, visited | bit, depth + 1);
        if (total >= ham_stop_after) {
            return total;
        }
    }
    return total;
}

static int graph_statistics(const Vertex *vertices, int n, int *edge_count,
                            int degree_counts[4], int cycle_limit) {
    for (int i = 0; i < n; ++i) {
        ham_adj[i] = 0;
    }
    for (int d = 0; d < 4; ++d) {
        degree_counts[d] = 0;
    }

    int edges = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacent(vertices[i], vertices[j])) {
                ham_adj[i] |= UINT64_C(1) << j;
                ham_adj[j] |= UINT64_C(1) << i;
                ++edges;
            }
        }
    }

    ham_start = 0;
    int minimum_degree = MAX_VERTICES;
    for (int i = 0; i < n; ++i) {
        int degree = popcount64(ham_adj[i]);
        if (degree < 0 || degree > 3) {
            fprintf(stderr, "unexpected honeycomb degree %d\n", degree);
            exit(2);
        }
        ++degree_counts[degree];
        if (degree < minimum_degree) {
            minimum_degree = degree;
            ham_start = i;
        }
    }
    *edge_count = edges;

    if (minimum_degree < 2) {
        return 0;
    }

    ham_n = n;
    ham_stop_after = cycle_limit * 2;
    int directed_cycles = hamiltonian_dfs(
        ham_start, UINT64_C(1) << ham_start, 1);
    if ((directed_cycles & 1) != 0) {
        fprintf(stderr, "odd directed Hamiltonian-cycle count %d\n", directed_cycles);
        exit(2);
    }
    return directed_cycles / 2;
}

static void record_polygon(int n) {
    ++rooted_polygons[n];

    int edge_count = 0;
    int degree_counts[4] = {0, 0, 0, 0};
    int cycles;

    /* With no chord, the enumerated perimeter is the unique cycle. */
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacent(path_vertices[i], path_vertices[j])) {
                ++edge_count;
            }
        }
    }
    if (edge_count == n) {
        cycles = 1;
    } else {
        ++chorded_polygons[n];
        cycles = graph_statistics(path_vertices, n, &edge_count, degree_counts, 2);
    }

    if (cycles < 1) {
        fprintf(stderr, "enumerated polygon at size %d lost its perimeter cycle\n", n);
        exit(2);
    }
    if (cycles > max_cycles[n]) {
        max_cycles[n] = cycles;
    }
}

static void enumerate_walks(int count) {
    Vertex current = path_vertices[count - 1];
    Vertex origin = path_vertices[0];

    if (count >= 6 && adjacent(current, origin)) {
        record_polygon(count);
    }
    if (count == MAX_N) {
        return;
    }

    Vertex next_vertices[3];
    neighbors(current, next_vertices);
    for (int i = 0; i < 3; ++i) {
        Vertex next = next_vertices[i];
        if (!in_grid(next) || same_vertex(next, origin) || is_occupied(next)) {
            continue;
        }

        /* After taking this edge, at most MAX_N-count edges remain to close. */
        if (lattice_distance_lower_bound(next) > MAX_N - count) {
            continue;
        }

        path_vertices[count] = next;
        set_occupied(next, true);
        enumerate_walks(count + 1);
        set_occupied(next, false);
    }
}

static int verify_s38(void) {
    static const Vertex s38[] = {
        {0,0,0}, {1,0,0}, {1,0,-1}, {2,0,-1}, {2,0,-2}, {2,1,-2},
        {2,1,-3}, {2,2,-3}, {1,2,-3}, {1,3,-3}, {1,3,-4}, {1,4,-4},
        {0,4,-4}, {0,5,-4}, {-1,5,-4}, {-1,5,-3}, {-2,5,-3},
        {-2,5,-2}, {-2,4,-2}, {-2,4,-1}, {-2,3,-1}, {-1,3,-1},
        {-1,3,-2}, {-1,4,-2}, {-1,4,-3}, {0,4,-3}, {0,3,-3},
        {0,3,-2}, {0,2,-2}, {1,2,-2}, {1,1,-2}, {1,1,-1}, {0,1,-1},
        {0,2,-1}, {-1,2,-1}, {-1,2,0}, {-1,1,0}, {0,1,0}
    };
    int n = (int)(sizeof(s38) / sizeof(s38[0]));
    int edges = 0;
    int degrees[4] = {0, 0, 0, 0};
    int cycles = graph_statistics(s38, n, &edges, degrees, 10);

    printf("S38 vertices=%d edges=%d degree2=%d degree3=%d cycles=%d\n",
           n, edges, degrees[2], degrees[3], cycles);
    if (n != 38 || edges != 49 || degrees[2] != 16 || degrees[3] != 22 ||
        degrees[0] != 0 || degrees[1] != 0 || cycles != 2) {
        fprintf(stderr, "S38 verification failed\n");
        return 1;
    }
    return 0;
}

int main(void) {
    Vertex origin = {0, 0, 0};
    Vertex first = {1, 0, 0};

    path_vertices[0] = origin;
    path_vertices[1] = first;
    set_occupied(origin, true);
    set_occupied(first, true);
    enumerate_walks(2);

    puts("Enumeration: rooted self-avoiding polygons with fixed directed edge");
    bool failed = false;
    for (int n = 1; n <= MAX_N; ++n) {
        printf("n=%d rooted_polygons=%" PRIu64 " chorded=%" PRIu64
               " max_undirected_hamiltonian_cycles=%d\n",
               n, rooted_polygons[n], chorded_polygons[n], max_cycles[n]);
        if (max_cycles[n] > 1) {
            failed = true;
        }
    }
    if (verify_s38() != 0) {
        failed = true;
    }

    if (failed) {
        fprintf(stderr, "Claim 14 minimum re-derivation: REFUTED\n");
        return 1;
    }
    puts("verdict=reproduces minimum (part (a) through 30; part (b) in full)");
    return 0;
}
