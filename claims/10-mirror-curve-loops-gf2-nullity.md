# Claim 10: Loop number of a polyomino's mirror curve equals the GF(2) nullity of its Laplacian

Status: open for review. Issue: [#8](https://github.com/pursekeeper/claims/issues/8).

**Field tags:** combinatorics, knot theory, graph theory, polyominoes

**Keywords:** mirror curve, Celtic knot, medial graph, straight-ahead walk, left-right path, spanning trees parity, Laplacian over GF(2), bicycle space, Tutte polynomial at (-1,-1)

**Related entries:** OEIS A397065 ("free polyominoes whose mirror curve consists of a single closed loop"; keywords "more, hard"; its comment says no general formula for the loop number is known), A131482; classical results: H. Shank, "The theory of left-right paths" (1975) and C. Godsil and G. Royle, Algebraic Graph Theory, Thm 17.3.5 (number of left-right cycles = 1 + dim bicycle space); P. Rosenstiehl and R. C. Read, "On the principal edge tripartition of a graph" (1978): T(G; -1, -1) = +-2^(dim bicycle space); mirror curves: S. Jablan, Lj. Radovic, R. Sazdanovic and A. Zekovic, "Mirror-curves and knot mosaics", arXiv:1106.3784; P. Gerdes, "Lunda Geometry" (2008)

## Statement

Let P be a free polyomino with n cells (holes allowed) and G its cell graph (vertices = cells, edges between side-sharing cells). The mirror curve of P is defined as follows. Place a point at the midpoint of every side of every cell. A ray travels inside P in one of the four diagonal directions (+-1, +-1); inside a cell it runs along a diagonal segment from the midpoint of one side to the midpoint of an adjacent side (a diagonal line of slope +-1 through the midpoint of one side of a unit square meets the midpoint of an adjacent side). On reaching the midpoint of a side that is shared with another cell of P, the ray continues straight into that cell (same direction). On reaching the midpoint of a side that is not shared (a boundary side, including the sides of holes), the ray reflects: the component of its direction perpendicular to that side changes sign, so it continues inside the same cell. Every such trajectory is closed; the loop number L(P) is the number of distinct closed trajectories (as unoriented point sets). For an a x b rectangle L = gcd(a, b). Let tau(P) be the number of spanning trees of G, and let nul(P) be the nullity (dimension of the kernel) over the field with two elements of the Laplacian matrix D - A of G (D the diagonal degree matrix, A the adjacency matrix). The claim has two parts. (a) For every free polyomino with n <= 11 cells, L(P) = nul(P). (b) For n = 1..17, the number of free n-cell polyominoes with tau(P) odd equals the number with L(P) = 1, which is the sequence 1, 1, 2, 4, 11, 28, 86, 273, 915, 3126, 10948, 38782, 138719, 499351, 1808081, 6576500, 24013937 (the terms listed in OEIS A397065).

## What a re-derivation must output to count

for part (a), a run over all free polyominoes with n <= 11 (23,546 shapes) reporting zero mismatches between L(P) computed by tracing the curve and nul(P) computed by Gaussian elimination over GF(2), together with the distribution of L (the maximum over n <= 11 is 4); for part (b), the counts of free n-cell polyominoes with an odd number of spanning trees for n = 1..17 as listed. Minimum: part (a) for n <= 11 and part (b) for n <= 12; full confirmation requires part (b) to n = 17.

## Novelty basis (as supplied)

the graph-theoretic fact "odd number of spanning trees iff exactly one left-right cycle" is a known corollary (M. Braverman, "Parity Problems in Planar Graphs", ECCC report 2007, Corollary 5; R. B. Richter, "Spanning trees, Euler tours, medial graphs, left-right paths and cycle spaces", Discrete Math. 89 (1991)). The identification of the mirror-curve loop number with the GF(2) Laplacian nullity, and hence of A397065 with polyominoes having an odd number of spanning trees, does not appear in the OEIS entry, its linked program and pages, or the mirror-curve literature, which calls the loop number an open problem. Part (a) was verified by one implementation and part (b) by two (n <= 12) plus agreement with the independently contributed OEIS terms to n = 17.

## Hardness (as supplied)

part (a) is seconds in Python; part (b) to n = 17 (50,107,909 free polyominoes, one determinant each) is about 40 CPU-minutes in C with an exact integer determinant, or seconds per n for n <= 12. A reviewer can also compute part (b) as "nul(P) = 1" if part (a) is accepted, but the claim is stated in terms of tau.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `aeba692072536677a93027244e98d5d37063e8f9f27055161693b0a612de4ec0`. Published here after the verdicts.
