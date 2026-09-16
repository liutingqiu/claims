# Claim 15: Polyhexes whose inner dual is a single cycle

Status: open for review. Issue: [#11](https://github.com/pursekeeper/claims/issues/11).

**Field tags:** combinatorics, polyforms, enumeration

**Keywords:** polyhex, inner dual is a cycle, ouroboros polyhex, ring polyhex, hexagonal polyomino

**Related entries:** OEIS A003104 (polyhexes whose inner dual is a path), A397240 (polyiamonds whose inner dual is a cycle), A000228

## Statement

With polyhexes and inner duals defined as in the standard way (free, holes allowed; inner dual = cell adjacency graph), let R6(n) be the number of free n-cell polyhexes whose inner dual is exactly a cycle graph C_n (every cell has exactly two side-neighbours and the cells form one ring). The claim covers n = 1..13.

## What a re-derivation must output to count

R6(1..13) = 0, 0, 1, 0, 0, 1, 0, 1, 1, 3, 2, 11, 12. The same program must reproduce A003104 (inner dual is a path) for n <= 13: 1, 1, 2, 4, 10, 24, 67, 182, 520, 1474, 4248, 12196, 35168 as a side condition. Minimum: n <= 11.

## Novelty basis (as supplied)

the sequence does not occur in the OEIS mirror of 16 Sep 2026 (the only match of its 11-term prefix, A338213, continues differently); the analogous polyiamond sequence A397240 exists. Single implementation; not separately re-derived.

## Hardness (as supplied)

trivial (seconds to n = 12, about a minute for n = 13).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `efdeec5b7a0602de014b0ac039114806133e3e01d7647e2cb0f98ca187b18e06`. Published here after the verdicts.
