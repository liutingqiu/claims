# Independent re-derivation of Claim 13

This directory independently checks the minimum acceptance range of Pursekeeper Claim
13. It does not use the claimant's unpublished code or another reviewer's code.

The primary enumerator grows self-avoiding walks and polygons after fixing one directed
edge, then canonicalizes each visited vertex set under translation and all 12 lattice
symmetries. This directly computes the sets whose induced graphs have Hamiltonian paths
or cycles. Fixing the edge loses no class: orient an edge of a Hamiltonian path or cycle,
translate its first endpoint to the chosen origin, and apply a lattice symmetry that maps
the second endpoint to the fixed neighbor. The triangular lattice gives P6/C6 through 12
cells; the honeycomb lattice gives P3/C3 through 18 cells.

A separate connected-shape growth algorithm enumerates every free polyhex through 12
cells and every free polyiamond through 15 cells for the required A000228/A000577 side
conditions. On every shape through eight cells, subset/end-vertex dynamic programming
independently decides Hamiltonian paths and cycles and is checked against the walk-based
enumerator.

Run offline with:

```sh
./run.sh
```

Validated output and hashes are recorded in `output.txt` and `SHA256SUMS` after the clean
Ubuntu run.

Validation used Ubuntu 24.04.4 LTS with GCC 13.3.0. A clean-directory optimized run took
24.79 wall seconds and 145,104 KiB maximum RSS. A full AddressSanitizer plus
UndefinedBehaviorSanitizer run took 249.16 seconds and 1,373,284 KiB maximum RSS, emitted
no diagnostics, and produced output byte-identical to `output.txt`. Both fit the published
10-minute, 4-GB sandbox limits.

SHA-256:

```text
adb7489fb5345926e4eade0e6cfd31a0e2f1fc8e1e76c03647fdded72be35403  verify_claim13.cpp
59894344f6bd7ac671058d99fec456294bcb87608f7885ab8841d96b3f104e0e  run.sh
2ff0fd4177af8c0ffc9fa5b584b7fc0cdd436ce881bbc70e0a711005e6e93a27  output.txt
```
