# Claim 4: Three further terms of OEIS A395587

Status: open for review. Issue: [#3](https://github.com/pursekeeper/claims/issues/3).

**Field tags:** number theory, primes, modular arithmetic, OEIS extension

**Keywords:** smallest prime, congruence modulo q^5, first n primes, p^(q^2) = +-1 mod q^5, Chinese remainder theorem

**Related entries:** OEIS A395587 (terms 1..7 in entry and b-file, keyword "more"), A396786 (companion with exponent q^3)

## Statement

Let a(n) be the smallest prime p such that for every prime q among the first n primes (2, 3, 5, 7, 11, ...) the congruence p^(q^2) = 1 (mod q^5) or p^(q^2) = -1 (mod q^5) holds. OEIS A395587 lists a(1..7) = 7, 271, 1999, 85751, 1329668999, 8655839869249, 2610206352778751. The claim gives a(8..10).

## What a re-derivation must output to count

a(1..10) = 7, 271, 1999, 85751, 1329668999, 8655839869249, 2610206352778751, 108845238471360544999, 111565602115338275478001, 698835425792323980459725999. Each of a(8), a(9), a(10) must be shown prime (a deterministic test or certificate; a probable-prime test is acceptable for a provisional verdict) and shown minimal, i.e. every smaller prime must fail the condition for some q. Minimum: a(8); full confirmation requires a(9) and a(10).

## Novelty basis (as supplied)

the OEIS entry and b-file end at a(7) (extended in July 2026); the three values are absent from the OEIS mirror of 16 Sep 2026 and from web search. In the original run the values were obtained by two methods within one session (a CRT search and an exhaustive residue-class enumeration in C with Lucas primality certificates) but were not re-derived by a separate blind reviewer.

## Hardness (as supplied)

cheap once one notes that (Z/q^5)* is cyclic of order q^4(q-1) for odd q, so the condition on p reduces to p = +-1 (mod q^3) for odd q and p = +-1 (mod 8) for q = 2; a CRT search over the 2^(n-1) sign choices, stepping through each arithmetic progression to its first prime, finishes in seconds in Python with gmpy2/sympy. A reviewer must verify that reduction (it can be brute-force checked against the literal definition for q <= 13) or work from the literal definition.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `728f9c79064c32372fc24765a72ad7eddfe636ac4c0fe8a315f9d00f8bdca725`. Published here after the verdicts.
