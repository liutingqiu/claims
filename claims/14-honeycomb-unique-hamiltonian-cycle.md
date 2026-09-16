# Claim 14: Hamiltonian induced subgraphs of the honeycomb lattice with more than one Hamiltonian cycle

Status: open for review. Issue: [#10](https://github.com/pursekeeper/claims/issues/10).

**Field tags:** graph theory, lattice statistics, self-avoiding polygons, honeycomb lattice

**Keywords:** honeycomb lattice, hexagonal lattice, induced subgraph, unique Hamiltonian cycle, self-avoiding polygon determined by vertex set, polyiamond inner dual

**Related entries:** OEIS A258206 (holeless polyhexes by perimeter), A000577; Claim-independent classical fact: the honeycomb lattice is 3-regular, bipartite and planar with girth 6

## Statement

Model the honeycomb (hexagonal) lattice as the graph whose vertices are the points (a, b, c) of Z^3 with a + b + c in {0, 1}, two vertices adjacent when they differ in exactly one coordinate by exactly 1; this is the 3-regular bipartite honeycomb graph. For a finite vertex set S consider the induced subgraph H[S]. The claim has two parts. (a) For every S with |S| <= 36 such that H[S] has a Hamiltonian cycle, H[S] has exactly one Hamiltonian cycle (as an undirected cycle). (b) The set S38 of 38 vertices (0,0,0) (1,0,0) (1,0,-1) (2,0,-1) (2,0,-2) (2,1,-2) (2,1,-3) (2,2,-3) (1,2,-3) (1,3,-3) (1,3,-4) (1,4,-4) (0,4,-4) (0,5,-4) (-1,5,-4) (-1,5,-3) (-2,5,-3) (-2,5,-2) (-2,4,-2) (-2,4,-1) (-2,3,-1) (-1,3,-1) (-1,3,-2) (-1,4,-2) (-1,4,-3) (0,4,-3) (0,3,-3) (0,3,-2) (0,2,-2) (1,2,-2) (1,1,-2) (1,1,-1) (0,1,-1) (0,2,-1) (-1,2,-1) (-1,2,0) (-1,1,0) (0,1,0) induces a subgraph with 49 edges (16 vertices of degree 2, 22 of degree 3) that has exactly two Hamiltonian cycles, and up to the symmetries of the lattice S38 is the only 38-vertex set with more than one Hamiltonian cycle. Equivalently, in terms of polyiamonds: every polyiamond with at most 36 cells whose inner dual is Hamiltonian has a unique Hamiltonian cycle, and the 38-cell polyiamond corresponding to S38 is the smallest with two.

## What a re-derivation must output to count

for part (b), the numbers 49 (edges), the degree multiset, and 2 (undirected Hamiltonian cycles of H[S38]); for part (a), an enumeration (of polyiamonds with a Hamiltonian inner dual, or of honeycomb self-avoiding polygons and their vertex sets) reporting that the maximum number of Hamiltonian cycles over all Hamiltonian vertex sets is 1 for every size up to 36, and that exactly one vertex set (up to symmetry) at size 38 has more than one. Minimum: part (b) in full and part (a) up to 30 vertices; full confirmation requires part (a) to 36 and the uniqueness at 38. The vertex-set counts by size that arise on the way (sizes 24..36: 97, 312, 744, 2291, 6186, 18714, 53793) may be reported for comparison with A258206 but are not part of the pass criterion.

## Novelty basis (as supplied)

the uniqueness phenomenon and its first failure at 38 vertices were found in the original run (one implementation verified uniqueness to 30 vertices, a second independently to 36 and found S38); the 38-vertex example was re-verified with a separate embedding and unpruned cycle count. No statement of either fact was found in OEIS or the literature; the question appears not to have been asked.

## Hardness (as supplied)

part (b) is instant; part (a) to 36 vertices requires enumerating honeycomb self-avoiding polygons to length 36 (or polyiamonds to 36 cells, which is heavier) and testing cycle counts only for vertex sets with chords, about 10-15 minutes in C.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `8e64caf0e880cba217dce6b54d6c0fcdf35816ee00b4be060c8096d8a8b9f299`. Published here after the verdicts.
