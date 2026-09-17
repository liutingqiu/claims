# Independent re-derivation of Claim 14

This directory independently checks the minimum acceptance range of Pursekeeper Claim
14. It does not use the claimant's unpublished code or another reviewer's code.

`verify_claim14.c` enumerates honeycomb-lattice self-avoiding polygons through 30
vertices after fixing one directed edge. Every finite honeycomb vertex set with a
Hamiltonian cycle occurs in this enumeration: orient any edge of that cycle from its
sum-0 endpoint to its sum-1 endpoint, translate the first endpoint to `(0,0,0)`, and
permute the three coordinates so the edge ends at `(1,0,0)`. For each enumerated
perimeter, the program builds the induced graph and counts its undirected Hamiltonian
cycles. Duplicate rooted embeddings are harmless because the requested statistic is a
maximum.

The same program independently builds the public 38-vertex input graph and computes its
edge count, degree multiset, and Hamiltonian-cycle count.

Run offline with:

```sh
./run.sh
```

The checked output and file hashes are recorded after the reproducible run in
`output.txt` and `SHA256SUMS`.

Validation on Ubuntu 24.04.4 LTS with GCC 13.3.0 completed in 0.98 wall seconds with
33,384 KiB maximum RSS. A clean-directory run and an AddressSanitizer plus
UndefinedBehaviorSanitizer run produced output identical to `output.txt`.

An independent Python checker used a different formulation for S38: removing one edge
at each degree-3 vertex is a perfect matching on the 22 degree-3 vertices. It found
three such matchings, exactly two of which leave a single connected 38-cycle. The same
checker canonicalized all enumerated vertex sets under translations and all 12 lattice
symmetries and reproduced the public comparison counts 97, 312, 744, and 2291 at sizes
24, 26, 28, and 30.

SHA-256:

```text
cdcdefac9cbbbfceadeea2df764e554d1ae0df430a03d00be7f751c0a7692f0d  verify_claim14.c
d6baeb94d76f2a1abe057905daaabcb6809be837ec3ea44bafa4943c22ecc9e0  run.sh
421619212318371783ad8ca8ada0922779dfc108917bfa95281419d48e061d37  output.txt
```
