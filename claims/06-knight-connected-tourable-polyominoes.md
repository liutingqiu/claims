# Claim 6: Knight-connected and knight-tourable polyominoes

Status: open for review. Issue: [#4](https://github.com/pursekeeper/claims/issues/4).

**Field tags:** recreational mathematics, chess, polyominoes, Hamiltonian paths

**Keywords:** knight's tour, knight graph, shaped boards, holey boards, tourable boards, polyomino boards, open tour, closed tour

**Related entries:** G. P. Jelliss, "Knight's Tour Notes", pages "The Smallest Knight-Tourable Boards, Part 1: Open Tours" (mayhematics.com/t/so.htm) and "Part 2: Closed Tours" (mayhematics.com/t/ss.htm), the latter incorporating counts by T. W. Marlow (1995) and A. Usher (2022); OEIS A030446 (polyknights, a different object), A001230 and A165134 (rectangular boards)

## Statement

Regard a free polyomino with n cells (holes allowed) as a chessboard. Its knight graph has the cells as vertices, two cells adjacent when they differ by (+-1, +-2) or (+-2, +-1). Define K(n) = number of free n-cell polyominoes whose knight graph is connected; O(n) = number admitting an open knight's tour, i.e. whose knight graph has a Hamiltonian path; C(n) = number admitting a closed knight's tour, i.e. whose knight graph has a Hamiltonian cycle. The claim covers n = 1..18. (For n = 1 the single cell counts as connected and open-tourable; C(n) = 0 for all odd n because the knight graph is bipartite under the chessboard colouring.)

## What a re-derivation must output to count

K(1..18) = 1, 0, 0, 0, 0, 0, 3, 28, 181, 904, 3908, 15802, 61443, 234343, 882684, 3307378, 12363082, 46213200;
O(1..18) = 1, 0, 0, 0, 0, 0, 2, 10, 57, 194, 617, 1580, 4858, 13124, 43487, 132176, 460301, 1481737;
C(1..18) = 0, 0, 0, 0, 0, 0, 0, 1, 0, 18, 0, 190, 0, 1346, 0, 10884, 0, 105983.
Minimum: all three sequences for n <= 14; full confirmation requires n = 15..18.

## Novelty basis (as supplied)

the cited pages give O(7) = 2, O(8) = 10, C(8) = 1, C(10) = 18, C(12) = 190 and state that complete enumeration exists only up to 12 cells (closed) and that asymmetric open tours on 10 or more cells were never counted; K(n) is not treated there or in OEIS. None of the three sequences, nor windows of them, nor the large terms occur in the OEIS mirror of 16 Sep 2026. Two independent implementations reproduce all 54 terms.

## Hardness (as supplied)

moderate. Polyomino enumeration to n = 18 (192,622,052 free) with bitmask DFS: about 11 minutes on two cores with degree and bipartition pruning; n <= 14 in under a minute.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `14c7825cedfa3832ece08dbc579b27fa612dca03b91a42d7d6c6824085c499d5`. Published here after the verdicts.
