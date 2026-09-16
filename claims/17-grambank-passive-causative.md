# Claim 17: Bound passive versus bound causative in Grambank: contingency tables

Status: open for review. Issue: [#13](https://github.com/pursekeeper/claims/issues/13).

**Field tags:** grammatical typology, morphology, databases

**Keywords:** Grambank, GB147, GB155, GB302, morphological passive, causative affix, valency-changing morphology, CLDF

**Related entries:** Grambank database, GitHub repository grambank/grambank, file cldf/values.csv at commit 37f73da55cf8b426c82383f46a972bc59ce6cf76 (MD5 of values.csv: 399c99b4fbf50c83eb6b6725028d2420); WALS chapter 107 (A. Siewierska, "Passive Constructions") and 111 (J. J. Song, "Nonperiphrastic Causative Constructions") and the WALS combination page 107A x 111A; D. Wunderlich, "Valency-changing word-formation" (HSK Word-Formation); M. Haspelmath, "The grammaticization of passive morphology", Studies in Language 14 (1990); Y. Ge and B. Comrie, "Correlations of valency alternations and morphological types", Lingua (2022); H. Skirgard et al., "Grambank reveals the importance of genealogical constraints on linguistic diversity", Science Advances 9 (2023)

## Statement

Take the Grambank CLDF values file at the commit above (columns include Language_ID, Parameter_ID, Value; the file covers 2,467 languages). Feature GB147 is "Is there a morphological passive marked on the lexical verb?", GB155 is "Are causatives formed by affixes or clitics on verbs?", GB302 is "Is there a phonologically free passive marker?" (wording as in cldf/parameters.csv at the same commit). For a pair of features, keep exactly the languages whose Value for both features is the string "0" or the string "1" (drop "?" and languages lacking a row for either feature). Table A crosses GB147 (rows) with GB155 (columns); Table B crosses GB302 (rows) with GB155 (columns).

*Note added by pursekeeper 2026-09-16 before posting: the MD5 supplied with this claim for values.csv was 399c99b4fbf50c83eb6b6725028d2420. The blob at the named commit (git object 9587fd1183a5ae88748d4b1353de4213b7790f2f, 51,545,673 bytes, checked with `git cat-file` on 2026-09-16) has MD5 60f1ae344334037c5064ce532300fae5. The claimant's own table code re-run on that blob gives the eight cells stated. The commit hash, not the MD5, pins the claim; the sandbox copy at `/data/grambank-values.csv` is that blob.*

## What a re-derivation must output to count

Table A (n = 1748): GB147 = 0 and GB155 = 0: 404; GB147 = 0 and GB155 = 1: 581; GB147 = 1 and GB155 = 0: 88; GB147 = 1 and GB155 = 1: 675. Table B (n = 1449): GB302 = 0, GB155 = 0: 292; GB302 = 0, GB155 = 1: 1009; GB302 = 1, GB155 = 0: 80; GB302 = 1, GB155 = 1: 68. All eight cells are required.

## Novelty basis (as supplied)

the tables are a deterministic property of the public dataset. No published statement of the dependence they show (a bound passive marker co-occurring with a causative affix in 88.5% of languages versus 59.0% otherwise) was found in the WALS chapters by Siewierska and Song, the Konstanz Universals Archive as far as searchable, or the valency literature (Wunderlich; Haspelmath 1990; Ge and Comrie 2022), which gives only marginal frequencies; a specialist would regard the direction as expected. The family- and area-controlled statistics are deliberately not part of this claim.

## Hardness (as supplied)

trivial (pandas, seconds). The dataset must be fetched at the stated commit.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `da4eaeb23c7c52760e97c14f4b38c5c980fe86f498c124c834f8ac2d66ee2bf7`. Published here after the verdicts.
