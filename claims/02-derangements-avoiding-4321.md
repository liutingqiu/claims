# Claim 2: Derangements avoiding the pattern 4321

Status: reserve (not yet open). Issue: see [claims/INDEX.md](INDEX.md).

**Field tags:** combinatorics, permutation patterns, derangements, enumeration

**Keywords:** pattern avoidance, 4321-avoiding, fixed-point-free permutations, longest decreasing subsequence, Av(4321)

**Related entries:** OEIS A005802 (4321-avoiders are equinumerous with 1234-avoiders), A000166, A318232

## Statement

Let b(n) be the number of permutations p of {1, ..., n} such that (i) p(i) is not equal to i for every i and (ii) there are no indices i < j < k < l with p(i) > p(j) > p(k) > p(l) (no decreasing subsequence of length 4, i.e. p avoids the classical pattern 4321). Note that reversal maps 1234-avoiders to 4321-avoiders but does not preserve the fixed-point condition, so this sequence differs from the 1234 case. The claim covers n = 1..24.

## What a re-derivation must output to count

b(1..24) = 0, 1, 2, 8, 34, 163, 842, 4616, 26530, 158496, 977974, 6201974, 40267062, 266836979, 1800228308, 12339445308, 85782771840, 603960294624, 4301125981958, 30949896861992, 224822477332698, 1647310789718374, 12166383404069430, 90516684013721640. Minimum: b(1..12).

## Novelty basis (as supplied)

same checks as for the 1234 case (OEIS mirror 16 Sep 2026, term windows and large individual terms; literature on pattern-avoiding derangements covers length-3 patterns only). Terms 22..24 from a single implementation; 1..21 from three.

## Hardness (as supplied)

as for the 1234 case; the decreasing-pile DP is somewhat faster (about 30 s for n <= 24).

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `9a0334ee760e30fc55f94bdf4062be90edef17eaa3fac8d48a2c2b98a4df588b`. Published here after the verdicts.
