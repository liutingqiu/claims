# Claim 13: Hamiltonian paths and cycles in the inner duals of polyhexes and polyiamonds

Status: open for review. Issue: [#9](https://github.com/pursekeeper/claims/issues/9).

**Field tags:** combinatorics, polyforms, chemical graph theory, Hamiltonian paths, lattice statistics

**Keywords:** polyhex, polyiamond, inner dual, dualist, Hamiltonian path, Hamiltonian cycle, self-avoiding walk vertex sets, triangular lattice, honeycomb lattice

**Related entries:** OEIS A000228 (free polyhexes), A000577 (free polyiamonds), A252653 and A361288 (the square-lattice analogues), A003104 (polyhexes whose inner dual is a path), A151518, A397240, A258206, A266925

## Statement

A polyhex with n cells is an edge-connected set of n cells of the regular hexagonal tiling; a polyiamond with n cells is an edge-connected set of n cells of the regular triangular tiling; both are counted free, i.e. up to translations, rotations and reflections (12 symmetries), holes allowed (OEIS A000228: 1, 1, 3, 7, 22, 82, 333, 1448, 6572, 30490, 143552, 683101, 3274826, 15796897, 76581875; A000577: 1, 1, 1, 3, 4, 12, 24, 66, 160, 448, 1186, 3334, 9235, 26166, 73983, 211297, 604107, 1736328, 5000593, 14448984, 41835738, 121419260). The inner dual of a polyform has one vertex per cell and an edge between two cells that share a side. Define P6(n), C6(n) = number of free n-cell polyhexes whose inner dual has a Hamiltonian path, respectively a Hamiltonian cycle; P3(n), C3(n) = the same for free n-cell polyiamonds (C3(n) = 0 for odd n since the triangular tiling's inner dual is bipartite). Equivalently, P6/C6 count distinct vertex sets of self-avoiding walks/polygons on the triangular lattice up to lattice symmetry, and P3/C3 the same on the honeycomb lattice. The claim covers n = 1..15 for polyhexes and n = 1..22 for polyiamonds.

## What a re-derivation must output to count

P6(1..15) = 1, 1, 3, 6, 20, 66, 246, 935, 3678, 14510, 57637, 228996, 910336, 3616389, 14358240;
C6(1..15) = 0, 0, 1, 1, 1, 4, 5, 14, 29, 82, 206, 625, 1800, 5670, 17787;
P3(1..22) = 1, 1, 1, 2, 3, 6, 9, 17, 29, 55, 98, 188, 343, 645, 1197, 2253, 4210, 7893, 14789, 27699, 51960, 97112;
C3(2, 4, ..., 22) = 0, 0, 1, 0, 1, 1, 3, 2, 12, 14, 50 (and 0 for all odd n).
The enumerators must reproduce A000228 (n <= 12) and A000577 (n <= 15) as side conditions. Minimum: P6, C6 for n <= 12 and P3, C3 for n <= 18; full confirmation requires the remaining terms.

## Novelty basis (as supplied)

none of P6, C6, P3 (beyond coincidental short prefixes) or any window of them occurs in the OEIS mirror of 16 Sep 2026; the OEIS polyhex/polyiamond entries and index pages contain only the "inner dual is a path / is a cycle" variants; E. C. Kirby, "Hamiltonian paths in polyhexes", J. Math. Chem. 4 (1990), concerns the carbon-skeleton graph, not the inner dual, and gives no counts. C3 coincides term for term with A258206 over the stated range. Two independent implementations agree on every listed term.

## Hardness (as supplied)

cheap to moderate; polyhexes to n = 15 (76.6 million free) about 10 CPU-minutes with pruning, polyiamonds to n = 22 (121 million free) similar.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `304a338eafe5475a5996f07250d08467d326464cc6aef6607a3406211e5e9784`. Published here after the verdicts.
