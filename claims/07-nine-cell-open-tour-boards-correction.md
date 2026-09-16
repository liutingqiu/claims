# Claim 7: Correction to the published count of open-tourable 9-cell boards

Status: open for review. Issue: [#5](https://github.com/pursekeeper/claims/issues/5).

**Field tags:** recreational mathematics, chess, polyominoes, correction

**Keywords:** knight's tour, 9-cell boards, smallest tourable boards, geometrically distinct tours, Jelliss, Knight's Tour Notes

**Related entries:** G. P. Jelliss, "Knight's Tour Notes", page "The Smallest Knight-Tourable Boards, Part 1: Open Tours", mayhematics.com/t/so.htm (enumeration check dated 17 July 2013)

## Statement

Consider the free 9-cell polyominoes (holes allowed) regarded as chessboards, and their knight graphs as in the previous definitions. A board is open-tourable if its knight graph has a Hamiltonian path. Tours are counted geometrically: for a board B let Aut(B) be the group of those of the 8 rotations/reflections of the plane that map B onto itself (after translation); two undirected Hamiltonian paths of the knight graph are the same tour if one is the image of the other under an element of Aut(B); the number of tours of B is the number of such orbits (Burnside over Aut(B), or canonicalisation of each path). The published count (page cited above) is 56 open-tourable 9-cell boards carrying 93 geometrically distinct open tours, with the boards whose bounding box is 4 x 4 broken down as one board with 6 tours, two symmetric boards with 4 tours each, one asymmetric board with 4 tours, one with 3, seven with 2, and 13 with exactly one tour. The claim is that the correct values are 57 boards and 94 tours, and that the only difference is one additional asymmetric board with 4 x 4 bounding box carrying exactly one tour (14 such boards, not 13); every other category agrees with the published breakdown.

## What a re-derivation must output to count

total 57 boards and 94 tours; the distribution of boards by number of tours: 34 boards with 1 tour, 15 with 2, 4 with 3, 3 with 4, 1 with 6; the breakdown by bounding box (boards / tours): 3 x 4: 7 / 11; 3 x 5: 12 / 17; 4 x 4: 26 / 49; 4 x 5 (either orientation): 11 / 16; 5 x 5: 1 / 1; and within the 4 x 4 frame: one board with 6 tours, three with 4, one with 3, seven with 2, fourteen with 1. All of these are required (the computation takes seconds).

## Novelty basis (as supplied)

the published page is the only prior enumeration; its 4 x 4 breakdown implies 25 boards / 48 tours where the claim finds 26 / 49, all other frames agreeing exactly. Two independent implementations (C++ with Burnside counting, Python with path canonicalisation) agree on 57 / 94 / 14. The published per-frame totals for 3 x 4 plus 3 x 5 (19 boards, 28 tours), 4 x 5 (11 boards, 16 tours) and 5 x 5 (1 / 1) agree with the claim.

## Hardness (as supplied)

trivial (1285 free 9-ominoes; seconds in Python).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `e81f9c541355576dff79c96cd137a5373cceabb024848afcae80fa0f8223b9ac`. Published here after the verdicts.
