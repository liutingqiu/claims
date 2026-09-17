# Index of claims

Seventeen seed claims supplied by the pilot's funder on 2026-09-16 (provenance: supplied by the pilot funder; prior work cited by author and title; the people who produced the claims are not identified; all produced by exhaustive computation on 16 September 2026). Claims are independent of each other. Every claim can be checked by running code; the pass criterion is term by term, no tolerances.

Conventions: a *free polyomino* is a finite edge-connected set of unit squares of the square grid, counted up to translations, rotations and reflections, holes allowed (OEIS A000105). The *cell graph* of a polyomino has one vertex per cell and an edge between two cells that share a side.

For every accepted claim the field tags, the keywords and the one-line *verified* entry below are kept so that a researcher scanning for checked small results can find them. The same data is in [`index.json`](index.json).

| # | Claim | Field tags | Status | Issue | Reviews accepted | Verified (what, how) |
|---|---|---|---|---|---|---|
| 1 | [Derangements avoiding the pattern 1234](01-derangements-avoiding-1234.md) | combinatorics, permutation patterns, derangements, enumeration | open | [#1](https://github.com/pursekeeper/claims/issues/1) | workesfm/ClearTable (reproduces, minimum a(1..12); terms 13..24 not evaluated) |  |
| 2 | [Derangements avoiding the pattern 4321](02-derangements-avoiding-4321.md) | combinatorics, permutation patterns, derangements, enumeration | reserve |  |  |  |
| 3 | [Six further terms of OEIS A252653 (rook-walk-coverable polyominoes)](03-A252653-rook-walk-coverable-polyominoes.md) | combinatorics, polyominoes, Hamiltonian paths, graph theory | open | [#2](https://github.com/pursekeeper/claims/issues/2) |  |  |
| 4 | [Three further terms of OEIS A395587](04-A395587-three-terms.md) | number theory, primes, modular arithmetic, OEIS extension | open | [#3](https://github.com/pursekeeper/claims/issues/3) |  |  |
| 5 | [Three further terms of OEIS A396786](05-A396786-three-terms.md) | number theory, primes, modular arithmetic, OEIS extension | reserve |  |  |  |
| 6 | [Knight-connected and knight-tourable polyominoes](06-knight-connected-tourable-polyominoes.md) | recreational mathematics, chess, polyominoes, Hamiltonian paths | open | [#4](https://github.com/pursekeeper/claims/issues/4) |  |  |
| 7 | [Correction to the published count of open-tourable 9-cell boards](07-nine-cell-open-tour-boards-correction.md) | recreational mathematics, chess, polyominoes, correction | open | [#5](https://github.com/pursekeeper/claims/issues/5) | workesfm/ClearTable (reproduces, full) |  |
| 8 | [Geometrically distinct knight's tours on polyomino boards](08-knight-tours-polyomino-boards.md) | recreational mathematics, chess, polyominoes, enumeration | open | [#6](https://github.com/pursekeeper/claims/issues/6) |  |  |
| 9 | [Polyknights admitting a knight's tour](09-polyknight-tours.md) | recreational mathematics, chess, polyforms, enumeration | open | [#7](https://github.com/pursekeeper/claims/issues/7) |  |  |
| 10 | [Loop number of a polyomino's mirror curve equals the GF(2) nullity of its Laplacian](10-mirror-curve-loops-gf2-nullity.md) | combinatorics, knot theory, graph theory, polyominoes | open | [#8](https://github.com/pursekeeper/claims/issues/8) |  |  |
| 11 | [Spanning-tree statistics of free polyominoes](11-spanning-tree-statistics-polyominoes.md) | combinatorics, polyominoes, spanning trees, extremal graph theory | reserve |  |  |  |
| 12 | [Independent-set and domino-tiling statistics of free polyominoes](12-independent-sets-domino-tilings-polyominoes.md) | combinatorics, polyominoes, statistical mechanics, hard squares, dimers | reserve |  |  |  |
| 13 | [Hamiltonian paths and cycles in the inner duals of polyhexes and polyiamonds](13-polyhex-polyiamond-inner-dual-hamiltonian.md) | combinatorics, polyforms, chemical graph theory, Hamiltonian paths, lattice statistics | open | [#9](https://github.com/pursekeeper/claims/issues/9) |  |  |
| 14 | [Hamiltonian induced subgraphs of the honeycomb lattice with more than one Hamiltonian cycle](14-honeycomb-unique-hamiltonian-cycle.md) | graph theory, lattice statistics, self-avoiding polygons, honeycomb lattice | open | [#10](https://github.com/pursekeeper/claims/issues/10) |  |  |
| 15 | [Polyhexes whose inner dual is a single cycle](15-ring-polyhexes.md) | combinatorics, polyforms, enumeration | open | [#11](https://github.com/pursekeeper/claims/issues/11) | workesfm/ClearTable (reproduces, full, n<=13 plus A003104 side condition) |  |
| 16 | [Ejectives versus the velar nasal in PHOIBLE: contingency tables](16-phoible-ejectives-velar-nasal.md) | phonological typology, phoneme inventories, databases | open | [#12](https://github.com/pursekeeper/claims/issues/12) | workesfm/ClearTable (reproduces, full, all eight cells) |  |
| 17 | [Bound passive versus bound causative in Grambank: contingency tables](17-grambank-passive-causative.md) | grammatical typology, morphology, databases | open | [#13](https://github.com/pursekeeper/claims/issues/13) | workesfm/ClearTable (reproduces, full, all eight cells) |  |

## Keywords

- **1** pattern avoidance, 1234-avoiding, fixed-point-free permutations, longest increasing subsequence, Av(1234), derangements in permutation classes
- **2** pattern avoidance, 4321-avoiding, fixed-point-free permutations, longest decreasing subsequence, Av(4321)
- **3** polyomino, complete self-avoiding walk, Hamiltonian path, cell adjacency graph, traceable, rook tour
- **4** smallest prime, congruence modulo q^5, first n primes, p^(q^2) = +-1 mod q^5, Chinese remainder theorem
- **5** smallest prime, congruence modulo q^5, first n primes, p^(q^3) = +-1 mod q^5
- **6** knight's tour, knight graph, shaped boards, holey boards, tourable boards, polyomino boards, open tour, closed tour
- **7** knight's tour, 9-cell boards, smallest tourable boards, geometrically distinct tours, Jelliss, Knight's Tour Notes
- **8** knight's tour, number of tours, symmetric tours, shaped boards, Burnside counting
- **9** polyknight, knight-connected cell sets, knight's tour, Hamiltonian path
- **10** mirror curve, Celtic knot, medial graph, straight-ahead walk, left-right path, spanning trees parity, Laplacian over GF(2), bicycle space, Tutte polynomial at (-1, -1)
- **11** number of spanning trees, Kirchhoff, matrix-tree theorem, polyomino cell graph, unicyclic polyominoes, maximum spanning trees
- **12** independent sets, hard-square model, Merrifield-Simmons index, domino tilings, perfect matchings, polyomino cell graph
- **13** polyhex, polyiamond, inner dual, dualist, Hamiltonian path, Hamiltonian cycle, self-avoiding walk vertex sets, triangular lattice, honeycomb lattice
- **14** honeycomb lattice, hexagonal lattice, induced subgraph, unique Hamiltonian cycle, self-avoiding polygon determined by vertex set, polyiamond inner dual
- **15** polyhex, inner dual is a cycle, ouroboros polyhex, ring polyhex, hexagonal polyomino
- **16** PHOIBLE, ejective consonants, velar nasal, raisedLarynxEjective, phoneme inventory co-occurrence
- **17** Grambank, GB147, GB155, GB302, morphological passive, causative affix, valency-changing morphology, CLDF

## Prior art reported

- none yet
