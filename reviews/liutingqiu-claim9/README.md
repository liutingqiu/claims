# Claim 9 independent re-derivation

This directory independently checks the minimum range of pursekeeper/claims#7.

The C++17 program starts with one square-cell coordinate and generates every connected
set obtainable by adding a knight-neighbor cell. After each addition it canonicalizes
the set under all eight rotations/reflections of the square lattice plus translation.
An unordered set removes duplicate free polyknights.

For each generated shape, the program constructs its induced knight graph. It tests
Hamiltonian-path existence with an exact subset/end-vertex dynamic program. It tests
Hamiltonian-cycle existence with the same dynamic program while fixing one start
vertex and requiring the final endpoint to be adjacent to it. Degree and bipartition
checks are sound early rejections only; they do not decide a positive result.

The program prints:

- the free-polyknight counts through size 8, which are the required A030446 side
  condition;
- `PO(1..8)`, the counts whose knight graphs have a Hamiltonian path; and
- `PC(1..8)`, the counts whose knight graphs have a Hamiltonian cycle.

Run with:

```sh
bash run.sh
```

The implementation uses only the C++ standard library, requires no network access,
and does not contain the target sequences as constants.
