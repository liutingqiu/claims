# Claim 5: Three further terms of OEIS A396786

Status: reserve (not yet open). Issue: see [claims/INDEX.md](INDEX.md).

**Field tags:** number theory, primes, modular arithmetic, OEIS extension

**Keywords:** smallest prime, congruence modulo q^5, first n primes, p^(q^3) = +-1 mod q^5

**Related entries:** OEIS A396786 (terms 1..8 in entry and b-file, keyword "more"), A395587

## Statement

Let a(n) be the smallest prime p such that for every prime q among the first n primes the congruence p^(q^3) = 1 (mod q^5) or p^(q^3) = -1 (mod q^5) holds. OEIS A396786 lists a(1..8) = 3, 17, 199, 22051, 387199, 52246349, 3753373051, 3884699495951. The claim gives a(9..11).

## What a re-derivation must output to count

a(1..11) = 3, 17, 199, 22051, 387199, 52246349, 3753373051, 3884699495951, 325259546614001, 161555206551161149, 55236433853128704749, with primality and minimality established as in the previous claim. Minimum: a(9).

## Novelty basis (as supplied)

as for A395587; the entry and b-file end at a(8); values absent from the OEIS mirror of 16 Sep 2026. Two methods in one session, no separate blind re-derivation in the original run.

## Hardness (as supplied)

cheap; for odd q the condition reduces to p = +-1 (mod q^2), and for q = 2 to p odd (p^8 = 1 mod 32 for every odd p); seconds with the CRT method.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `728f9c79064c32372fc24765a72ad7eddfe636ac4c0fe8a315f9d00f8bdca725`. Published here after the verdicts.
