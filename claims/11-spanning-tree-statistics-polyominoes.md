# Claim 11: Spanning-tree statistics of free polyominoes

Status: reserve (not yet open). Issue: see [claims/INDEX.md](INDEX.md).

**Field tags:** combinatorics, polyominoes, spanning trees, extremal graph theory

**Keywords:** number of spanning trees, Kirchhoff, matrix-tree theorem, polyomino cell graph, unicyclic polyominoes, maximum spanning trees

**Related entries:** OEIS A131482 (tree polyominoes: tau = 1), A007341 and A001353 (spanning trees of rectangles), A000105

## Statement

For a free polyomino P with n cells (holes allowed) let tau(P) be the number of spanning trees of its cell graph. Define M(n) = max tau(P) over all free n-cell polyominoes; NM(n) = number of free n-cell polyominoes attaining M(n); SUM(n) = sum of tau(P) over all free n-cell polyominoes; DIST(n) = number of distinct values taken by tau over free n-cell polyominoes; UNI(n) = number of free n-cell polyominoes whose cell graph has exactly n edges (exactly one cycle). The claim covers n = 1..17.

## What a re-derivation must output to count

M(1..17) = 1, 1, 1, 4, 4, 15, 16, 56, 192, 209, 712, 2415, 2656, 8960, 30305, 100352, 112456;
NM(1..17) = 1, 1, 2, 1, 1, 1, 1, 2, 1, 3, 1, 1, 2, 1, 1, 1, 1;
SUM(1..17) = 1, 1, 2, 8, 15, 70, 228, 1053, 4267, 19368, 86008, 405110, 1876813, 8931533, 42425703, 203946180, 981407167;
DIST(1..17) = 1, 1, 1, 2, 2, 3, 4, 6, 8, 13, 18, 27, 42, 69, 113, 196, 337;
UNI(1..17) = 0, 0, 0, 1, 1, 7, 21, 91, 339, 1360, 5255, 20510, 79235, 306353, 1179603, 4536616, 17412438.
The distribution of tau for n = 1..12 must also reproduce A131482 (number of polyominoes with tau = 1) as a side condition. Minimum: all five sequences for n <= 13; full confirmation requires n = 14..17.

## Novelty basis (as supplied)

none of the five sequences, nor any window of four consecutive terms, nor the large individual terms occur in the OEIS mirror of 16 Sep 2026; web searches for "polyominoes" with "number of spanning trees" and for the term windows found nothing. Single implementation (exact Bareiss determinants, cross-checked against floating-point LU on all shapes with n <= 14 and against an independent Python implementation for n <= 9); the odd-tau column of the same run matches A397065 to n = 17. Not separately re-derived.

## Hardness (as supplied)

n <= 13 in a couple of minutes in C; n = 17 about 40 CPU-minutes (the same run also yields the two following claims).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `d984708c20adc9b7c583f9a2738860fa8aa60f493b4fef31c1e3d3235768855b`. Published here after the verdicts.
