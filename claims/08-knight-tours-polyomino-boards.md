# Claim 8: Geometrically distinct knight's tours on polyomino boards

Status: open for review. Issue: [#6](https://github.com/pursekeeper/claims/issues/6).

**Field tags:** recreational mathematics, chess, polyominoes, enumeration

**Keywords:** knight's tour, number of tours, symmetric tours, shaped boards, Burnside counting

**Related entries:** G. P. Jelliss, "Knight's Tour Notes" (mayhematics.com/t/so.htm, /t/ss.htm), with contributions by T. W. Marlow (1995) and A. Usher (2022), gives: 12-cell closed tours 190 boards / 236 tours / 27 symmetric; 14-cell closed symmetric tours 58; symmetric open tours on 9, 10, 11, 12 cells: 10, 9, 37, 49

## Statement

Boards, knight graphs and Aut(B) as in the preceding definitions (free n-cell polyominoes, holes allowed). For each board count the orbits of undirected Hamiltonian paths of its knight graph under Aut(B) (open tours) and the orbits of undirected Hamiltonian cycles under Aut(B) (closed tours); a tour is symmetric if its orbit is fixed by some non-identity element of Aut(B) (equivalently the orbit has fewer than |Aut(B)| elements). Define T_open(n), T_closed(n), S_open(n), S_closed(n) as the totals over all boards with n cells, and R_open(n), R_closed(n) as the raw totals of undirected Hamiltonian paths and cycles without dividing out symmetry. The claim covers n = 7..16.

## What a re-derivation must output to count

T_open(7..16) = 2, 13, 94, 577, 2083, 10011, 33446, 150354, 515061, 2362600;
T_closed(7..16) = 0, 1, 0, 19, 0, 236, 0, 2423, 0, 29593;
S_open(7..16) = 2, 1, 10, 9, 37, 49, 128, 217, 521, 893;
S_closed(7..16) = 0, 1, 0, 4, 0, 27, 0, 58, 0, 271;
R_open(7..16) = 2, 20, 104, 610, 2151, 10568, 33983, 152288, 519343, 2393762;
R_closed(7..16) = 0, 1, 0, 19, 0, 242, 0, 2449, 0, 30068.
Minimum: all six sequences for n <= 12 (these include the published 190 / 236 / 27 check); full confirmation requires n = 13..16.

## Novelty basis (as supplied)

the published pages cover closed tours completely only to 12 cells and asymmetric open tours only to 9 cells; the values that overlap with them (n <= 12 closed, symmetric counts, n <= 9 open after the correction in the previous claim) agree. Values for n >= 13 (open) and n >= 14 (closed totals) come from a single implementation in the original run and were not separately re-derived except for the board counts.

## Hardness (as supplied)

cheap; n = 16 in about 75 s single-threaded in C.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `9a00287f006817533ec7e565c035f209501bfc14646d558cd43bf6e4c6bbdb50`. Published here after the verdicts.
