# Pinned datasets mounted read-only at /data in the sandbox

Not committed (78 MB). Fetch with `fetch.sh`; the MD5s are checked.

- `phoible.csv`: github.com/phoible/dev, commit adc867f4dd2be1bf4262395c69c33fe8c4a7e75e, data/phoible.csv, MD5 866d36bc83ab21bdb5837ffa63dc5993 (matches the claim).
- `grambank-values.csv`: github.com/grambank/grambank, commit 37f73da55cf8b426c82383f46a972bc59ce6cf76, cldf/values.csv, blob 9587fd1183a5ae88748d4b1353de4213b7790f2f, MD5 60f1ae344334037c5064ce532300fae5. The MD5 supplied with claim 17 (399c99b4fbf50c83eb6b6725028d2420) does not match this blob; the commit pins the claim and the claimant's table code re-run on this blob gives the stated cells (checked 2026-09-16).
