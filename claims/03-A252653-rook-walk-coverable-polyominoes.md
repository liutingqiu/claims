# Claim 3: Six further terms of OEIS A252653 (rook-walk-coverable polyominoes)

Status: open for review. Issue: [#2](https://github.com/pursekeeper/claims/issues/2).

**Field tags:** combinatorics, polyominoes, Hamiltonian paths, graph theory

**Keywords:** polyomino, complete self-avoiding walk, Hamiltonian path, cell adjacency graph, traceable, rook tour

**Related entries:** OEIS A252653 (terms 1..12 only, keyword "more"), A361288 (Hamiltonian cycle version), A283162, A000105

## Statement

Let a(n) be the number of free polyominoes with n cells (holes allowed) whose cell graph (cells adjacent when they share a side) contains a Hamiltonian path, i.e. the polyomino can be covered by a single self-avoiding rook walk that visits every cell exactly once. OEIS A252653 lists a(1..12) = 1, 1, 2, 4, 8, 18, 46, 115, 300, 781, 2097, 5541. The claim gives a(13..18).

## What a re-derivation must output to count

a(1..18) = 1, 1, 2, 4, 8, 18, 46, 115, 300, 781, 2097, 5541, 14916, 39592, 106630, 283409, 761763, 2024680. Minimum: a(13..15); full confirmation requires a(16..18).

## Novelty basis (as supplied)

the OEIS entry, its b-file and the source page it links (E. French, "Covering Free Polyominos", fuseki.net/polycover/index.html) all stop at n = 12; the six new terms and the window ",5541,14916," do not occur anywhere in the OEIS mirror of 16 Sep 2026; web and literature searches found nothing beyond n = 12. Two independent implementations agree on all six terms.

## Hardness (as supplied)

cheap. Redelmeier enumeration of fixed polyominoes with canonical-form reduction to free ones, plus a bitmask DFS for Hamiltonian paths with leaf-count and bipartition pruning: n = 18 in about 90 s wall on two cores (roughly 15 CPU-minutes without pruning).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `564da16f60b394d42fd49d9042a8029eb4015552a60a0a3654c62bce2d119df3`. Published here after the verdicts.
