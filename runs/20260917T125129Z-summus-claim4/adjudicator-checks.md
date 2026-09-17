# Adjudicator checks on the Summus Code review of claim 4 (2026-09-17)

These are pursekeeper's own checks, made after the sandbox run and not part of the reviewer's submission.

## 1. The reduction lemma

The reviewer's search enumerates the residue classes p ≡ ±1 (mod q³) for odd q and p ≡ ±1 (mod 8) for q = 2 and steps each progression to its first prime; minimality of the result depends on that reduction being an equivalence with the literal condition p^(q²) ≡ ±1 (mod q⁵). The program asserts the reduction and verifies the literal condition only for the value it finds. Brute force over every unit r mod q⁵, comparing `pow(r, q*q, q**5) in (1, q**5-1)` with `r % m in (1, m-1)` (m = 8 for q = 2, q³ otherwise):

```
q   mismatches
2   0
3   0
5   0
7   0
11  0
13  0
(0.3 s, CPython 3)
```

For q ≥ 17 the equivalence follows from (Z/q⁵)* being cyclic of order q⁴(q−1): the elements of order dividing 2q² and the elements ≡ ±1 (mod q³) are both subgroups of order 2q², hence equal.

## 2. Deterministic primality of a(8), a(9), a(10)

The sandbox run tested primality with `sympy.isprime`, which is a BPSW probable-prime test above 2⁶⁴; the claim's criterion calls that provisional. Pocklington (n−1) certificates, computed with sympy's `factorint` for the factorisation of n−1 (every prime factor below 2⁶⁴, where `isprime` is deterministic), factored part F > √n, witness a = 2 satisfying a^(n−1) ≡ 1 and gcd(a^((n−1)/q) − 1, n) = 1 for each prime q | F:

```
a(8)=108845238471360544999 n-1 factors={2: 1, 3: 4, 13: 3, 17: 3, 47: 1, 557: 1, 2377741: 1} F>sqrt: True pocklington_ok=True cert=[(2377741, 1, 2), (557, 1, 2), (47, 1, 2)] secs=0.0
a(9)=111565602115338275478001 n-1 factors={2: 4, 3: 4, 5: 3, 7: 3, 17: 3, 19: 3, 23: 3, 59: 1, 83: 1} F>sqrt: True pocklington_ok=True cert=[(83, 1, 2), (59, 1, 2), (23, 3, 2), (19, 3, 2)] secs=0.0
a(10)=698835425792323980459725999 n-1 factors={2: 1, 11: 3, 13: 3, 17: 3, 23: 3, 1998971177167: 1} F>sqrt: True pocklington_ok=True cert=[(1998971177167, 1, 2), (23, 3, 2)] secs=0.0
```

With these, the reviewer's reproduction of a(8..10) is full, not provisional.
