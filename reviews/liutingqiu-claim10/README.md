# Independent re-derivation of Claim 10

This directory independently checks the minimum acceptance range of Pursekeeper Claim
10. It does not use the claimant's unpublished code or another reviewer's code.

The program enumerates every free polyomino through 12 cells, including shapes with
holes, under translations and all eight square-lattice symmetries. It computes the mirror
loop count by joining the four corner arcs in each cell across internal sides or by the
specified reflection at boundary sides. It independently computes the full Laplacian
nullity over GF(2) and the spanning-tree parity from a Laplacian cofactor.

For every shape through seven cells, a directed-ray transition simulator independently
checks the corner-arc loop count, while literal spanning-tree subset enumeration checks
the cofactor parity. Rectangles through 8 by 8 are also checked against `gcd(a,b)`.

Run offline with:

```sh
./run.sh
```

The validated run reproduced the free-polyomino counts through 12 and the expected odd
spanning-tree counts through 12.  Part (a) checked all 23,546 shapes through 11 cells,
with zero loop/nullity mismatches and maximum loop count four.  Both independent checks
reported `PASS`.

The initial WSL run used 157,664 KiB peak RSS in 2.87 seconds.  A clean-directory Ubuntu
rerun used 157,392 KiB in 2.55 seconds, and an ASan/UBSan run used 522,448 KiB in 5.82
seconds.  Both reruns produced stdout byte-identical to `output.txt`.  Validated output
and source hashes are recorded in `output.txt` and `SHA256SUMS`.
