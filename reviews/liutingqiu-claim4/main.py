#!/usr/bin/env python3
import heapq
import math

from sympy import factorint, isprime, nextprime


U64_LIMIT = 1 << 64
U64_MILLER_RABIN_BASES = (2, 325, 9375, 28178, 450775, 9780504, 1795265022)


def first_primes(count):
    result = []
    value = 1
    for _ in range(count):
        value = int(nextprime(value))
        result.append(value)
    return result


def crt_pair(a, modulus_a, b, modulus_b):
    step = ((b - a) * pow(modulus_a, -1, modulus_b)) % modulus_b
    modulus = modulus_a * modulus_b
    return (a + step * modulus_a) % modulus, modulus


def residue_classes(primes):
    residues = [0]
    modulus = 1
    for q in primes:
        local_modulus = 8 if q == 2 else q**3
        choices = (1, local_modulus - 1)
        expanded = []
        for residue in residues:
            for choice in choices:
                combined, combined_modulus = crt_pair(
                    residue, modulus, choice, local_modulus
                )
                expanded.append(combined)
        modulus = combined_modulus
        residues = sorted(set(expanded))
    if len(residues) != 1 << len(primes):
        raise RuntimeError("CRT sign classes were not unique")
    return residues, modulus


def deterministic_u64_prime(n):
    if n < 2:
        return False
    small_primes = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37)
    for prime in small_primes:
        if n % prime == 0:
            return n == prime

    d = n - 1
    power_of_two = 0
    while d % 2 == 0:
        power_of_two += 1
        d //= 2

    for base in U64_MILLER_RABIN_BASES:
        if base % n == 0:
            continue
        value = pow(base, d, n)
        if value in (1, n - 1):
            continue
        for _ in range(power_of_two - 1):
            value = value * value % n
            if value == n - 1:
                break
        else:
            return False
    return True


def pocklington_proof(n, memo):
    if n in memo:
        return memo[n]
    if n < U64_LIMIT:
        if not deterministic_u64_prime(n):
            raise ValueError(f"{n} is not prime")
        proof = {"kind": "deterministic-u64"}
        memo[n] = proof
        return proof

    factors = {int(q): int(exponent) for q, exponent in factorint(n - 1).items()}
    reconstructed = math.prod(q**exponent for q, exponent in factors.items())
    if reconstructed != n - 1 or reconstructed <= math.isqrt(n):
        raise RuntimeError(f"incomplete Pocklington factorization for {n}")

    witnesses = {}
    for q in sorted(factors):
        pocklington_proof(q, memo)
        for witness in range(2, 10_000):
            fermat = pow(witness, n - 1, n) == 1
            coprime = math.gcd(pow(witness, (n - 1) // q, n) - 1, n) == 1
            if fermat and coprime:
                witnesses[q] = witness
                break
        else:
            raise RuntimeError(f"no Pocklington witness found for n={n}, q={q}")

    proof = {"kind": "pocklington", "factors": factors, "witnesses": witnesses}
    memo[n] = proof
    return proof


def smallest_prime(primes, proof_memo):
    residues, modulus = residue_classes(primes)
    queue = []
    for residue in residues:
        candidate = residue if residue >= 2 else residue + modulus
        heapq.heappush(queue, (candidate, residue))

    tested = 0
    while queue:
        candidate, residue = heapq.heappop(queue)
        tested += 1
        if isprime(candidate):
            proof = pocklington_proof(candidate, proof_memo)
            return candidate, modulus, len(residues), tested, proof
        heapq.heappush(queue, (candidate + modulus, residue))
    raise RuntimeError("unreachable: every reduced residue class is coprime to the modulus")


def literal_condition(candidate, primes):
    for q in primes:
        modulus = q**5
        if pow(candidate, q * q, modulus) not in (1, modulus - 1):
            return False
    return True


def check_reduction():
    for q in first_primes(6):
        modulus = q**5
        reduced_modulus = 8 if q == 2 else q**3
        for value in range(1, modulus):
            if math.gcd(value, q) != 1:
                continue
            literal = pow(value, q * q, modulus) in (1, modulus - 1)
            reduced = value % reduced_modulus in (1, reduced_modulus - 1)
            if literal != reduced:
                raise RuntimeError(f"reduction mismatch for q={q}, residue={value}")


def format_factorization(factors):
    return " * ".join(
        str(q) if exponent == 1 else f"{q}^{exponent}"
        for q, exponent in sorted(factors.items())
    )


def main():
    check_reduction()
    primes = first_primes(10)
    proof_memo = {}
    values = []
    details = []

    for n in range(1, 11):
        value, modulus, classes, tested, proof = smallest_prime(
            primes[:n], proof_memo
        )
        if not literal_condition(value, primes[:n]):
            raise RuntimeError(f"literal congruence failed for a({n})")
        values.append(value)
        details.append((n, value, modulus, classes, tested, proof))

    print("reduction check for q <= 13: PASS")
    print("a(1..10) = " + ", ".join(map(str, values)))
    for n, value, modulus, classes, tested, proof in details:
        method = proof["kind"]
        print(
            f"a({n}): p={value}; modulus={modulus}; sign_classes={classes}; "
            f"ordered_candidates_tested={tested}; literal=PASS; primality={method}"
        )
        if method == "pocklington":
            factorization = format_factorization(proof["factors"])
            witnesses = ",".join(
                f"{q}:{witness}" for q, witness in sorted(proof["witnesses"].items())
            )
            print(f"  p-1 = {factorization}; witnesses(q:a)={witnesses}")


if __name__ == "__main__":
    main()
