# Claim 1: Derangements avoiding the pattern 1234

Status: open for review. Issue: [#1](https://github.com/pursekeeper/claims/issues/1).

**Field tags:** combinatorics, permutation patterns, derangements, enumeration

**Keywords:** pattern avoidance, 1234-avoiding, fixed-point-free permutations, longest increasing subsequence, Av(1234), derangements in permutation classes

**Related entries:** OEIS A005802 (1234-avoiding permutations), A000166 (derangements), A318232 (123-avoiding derangements), A258041, A393394; V. Vatter, "An assortment of problems in permutation patterns", arXiv:2602.16355 (2026), section on derangements in permutation classes; S. Elizalde, "Fixed points and excedances in restricted permutations", Electron. J. Combin. 18(2) (2011)

## Statement

Let a(n) be the number of permutations p of {1, ..., n} such that (i) p(i) is not equal to i for every i (no fixed points) and (ii) there are no indices i < j < k < l with p(i) < p(j) < p(k) < p(l) (no increasing subsequence of length 4, i.e. p avoids the classical pattern 1234). The claim covers n = 1..24.

## What a re-derivation must output to count

a(1..24) = 0, 1, 2, 9, 42, 221, 1242, 7299, 44866, 283733, 1851110, 12338897, 84105038, 583025833, 4109777878, 29362605297, 212530337808, 1555219528353, 11499793687156, 85802842585877, 645694658920438, 4895863049205031, 37388255442259582, 287356916298447781. Minimum for a partial confirmation: a(1..12); full confirmation requires all 24 terms.

## Novelty basis (as supplied)

no window of three consecutive terms and none of the large individual terms occurs in a mirror of the full OEIS database (oeisdata git mirror, snapshot 16 Sep 2026, 399,272 sequences); the underlying triangle "1234-avoiders by number of fixed points" is likewise absent; the 2026 survey by Vatter (arXiv:2602.16355) and the located literature on pattern-avoiding derangements (Elizalde 2011; Fu, Tang, Han and Zeng, arXiv:1805.08945; Henke, Stephens and Zhuang, arXiv:2608.11085; Dougherty-Bliss, Galvan, Polley and Shuster, arXiv:2608.27583) treat only length-3 patterns and separable permutations; no generating function in the literature produces these numbers. Terms 22..24 come from a single implementation; terms 1..21 from three.

## Hardness (as supplied)

n <= 12 by brute force over all n! permutations in a few minutes (C); all 24 terms by an exact dynamic programme over (used-value bitmask, patience-sorting piles) in about two minutes in C++; n = 21 by a hash-map DP needs a few GB of RAM, n = 24 by the rank-compressed DP needs very little.

## Open observation (not a claim)

the ratio a(n)/A005802(n) increases monotonically over the computed range (0.476 at n = 9, 0.529 at n = 21).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `593cae88d2b22dbbe3283cbb3b7db97feb7cce8d37500829c39a3728a3c82b2a`. Published here after the verdicts.
