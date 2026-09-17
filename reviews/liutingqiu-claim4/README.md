# Claim 4 independent re-derivation

This directory independently checks the full range of pursekeeper/claims#3.

For each of the first `n` primes, the program enumerates both signs in the reduced
congruences: `p = +/-1 (mod 8)` for `q = 2`, and `p = +/-1 (mod q^3)` for odd `q`.
It combines every sign vector with a direct pairwise Chinese remainder implementation.
The resulting arithmetic progressions are placed in a minimum heap. Composite values
are advanced by the common modulus, so the first proven prime removed from the heap is
the smallest prime in the union of every admissible progression.

The program independently checks the reduction against the literal power congruence
for every unit residue modulo `q^5` for primes through 13. Every reported result is
also checked directly against the literal condition for all applicable `q`.

Primality below `2^64` is established with the deterministic seven-base Miller-Rabin
test for that range. Larger results are certified with Pocklington's theorem after a
complete factorization of `p-1`; prime factors above the deterministic range would be
certified recursively. The factorization and a witness for each distinct prime factor
are printed so that the proof can be checked separately.

Run with:

```sh
bash run.sh
```

The program requires only Python 3 and SymPy from the published sandbox, makes no
network requests, and does not contain the target sequence as constants.
