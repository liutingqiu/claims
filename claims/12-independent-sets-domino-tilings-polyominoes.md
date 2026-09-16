# Claim 12: Independent-set and domino-tiling statistics of free polyominoes

Status: reserve (not yet open). Issue: see [claims/INDEX.md](INDEX.md).

**Field tags:** combinatorics, polyominoes, statistical mechanics, hard squares, dimers

**Keywords:** independent sets, hard-square model, Merrifield-Simmons index, domino tilings, perfect matchings, polyomino cell graph

**Related entries:** OEIS A006506 and A001333 (independent sets of rectangles), A004003 (domino tilings of rectangles), A213376-A213378 (polyominoes by number of domino tilings 0, 1, >= 2), A000105

## Statement

For a free polyomino P with n cells (holes allowed) let i(P) be the number of independent sets of its cell graph (sets of cells no two of which share a side, the empty set included) and m(P) the number of perfect matchings of its cell graph (domino tilings). Define IMIN(n) = min i(P), IMAX(n) = max i(P), ISUM(n) = sum of i(P), IDIST(n) = number of distinct values of i(P), all over free n-cell polyominoes, for n = 1..17; and for even n = 2k, MSUM(k) = sum of m(P) and MMAX(k) = max m(P) over free 2k-cell polyominoes, for k = 1..8.

## What a re-derivation must output to count

IMIN(1..17) = 2, 3, 5, 7, 12, 17, 29, 41, 63, 99, 155, 227, 373, 555, 827, 1234, 2027;
IMAX(1..17) = 2, 3, 5, 9, 17, 26, 43, 77, 145, 225, 370, 659, 1237, 1921, 3158, 5642, 10555;
ISUM(1..17) = 2, 3, 10, 40, 162, 753, 3798, 21030, 119424, 702997, 4197836, 25435079, 155276651, 955009277, 5903249062, 36660571982, 228517995526;
IDIST(1..17) = 1, 1, 1, 3, 4, 8, 14, 26, 45, 89, 155, 288, 502, 910, 1609, 2842, 4994;
MSUM(1..8) = 1, 5, 27, 264, 2896, 35679, 454900, 5957531;
MMAX(1..8) = 1, 2, 3, 5, 8, 13, 21, 36.
The distribution of m(P) must reproduce A213376 and A213377 for 2k <= 16 as a side condition. Minimum: all sequences for n <= 13 (k <= 6); full confirmation requires n = 14..17 (k = 7, 8).

## Novelty basis (as supplied)

none of the six sequences or their windows occur in the OEIS mirror of 16 Sep 2026 (the domino-tiling columns A213376-8 do, and were used as validation); single implementation with an independent Python check for n <= 9; not separately re-derived.

## Hardness (as supplied)

as for the previous claim (same enumeration run).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `daa62d6ab8bd60a8338910760440fe8dc6b269d0d9f1cab8dc29689da1350c08`. Published here after the verdicts.
