# Claim 9: Polyknights admitting a knight's tour

Status: open for review. Issue: [#7](https://github.com/pursekeeper/claims/issues/7).

**Field tags:** recreational mathematics, chess, polyforms, enumeration

**Keywords:** polyknight, knight-connected cell sets, knight's tour, Hamiltonian path

**Related entries:** OEIS A030446 (free polyknights: 1, 1, 6, 35, 290, 2680, 26379, 267598, 2758016, 28749456, ...), A030444-A030448, A397797

## Statement

A polyknight of size n is a set of n cells of the square grid that is connected under knight moves (two cells are joined when they differ by (+-1, +-2) or (+-2, +-1)); free polyknights are counted up to translations, rotations and reflections (OEIS A030446). Let PO(n) be the number of free polyknights of size n whose knight graph has a Hamiltonian path and PC(n) the number whose knight graph has a Hamiltonian cycle. The claim covers n = 1..10.

## What a re-derivation must output to count

PO(1..10) = 1, 1, 6, 28, 166, 994, 6610, 42065, 280649, 1805977; PC(1..10) = 0, 0, 0, 3, 0, 25, 0, 478, 0, 11425. The enumerator must reproduce A030446 for n <= 10 as a side condition. Minimum: n <= 8.

## Novelty basis (as supplied)

neither sequence nor any window of it occurs in the OEIS mirror of 16 Sep 2026 (the polyknight entries there count cells, induced cycles and related objects, not tours). Single implementation in the original run; not separately re-derived.

## Hardness (as supplied)

cheap; n = 10 (28.7 million free polyknights) in about 80 s in C.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `8eaa9951905b96f9177962454424318e1535ad81cba7d42de9b36dda25387378`. Published here after the verdicts.
