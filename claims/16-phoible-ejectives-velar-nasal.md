# Claim 16: Ejectives versus the velar nasal in PHOIBLE: contingency tables

Status: open for review. Issue: [#12](https://github.com/pursekeeper/claims/issues/12).

**Field tags:** phonological typology, phoneme inventories, databases

**Keywords:** PHOIBLE, ejective consonants, velar nasal, raisedLarynxEjective, phoneme inventory co-occurrence

**Related entries:** PHOIBLE database, GitHub repository phoible/dev, file data/phoible.csv at commit adc867f4dd2be1bf4262395c69c33fe8c4a7e75e (MD5 of the CSV: 866d36bc83ab21bdb5837ffa63dc5993); WALS chapter 7 (I. Maddieson, "Glottalized Consonants"), chapter 9 (G. D. S. Anderson, "The Velar Nasal") and the WALS feature combination page 7A x 9A; J. Lee, "Phonological Typology of Velar Nasals", Gengo Kenkyu 168 (2025); I. Maddieson, Patterns of Sounds (1984); D. Nikolaev and E. Grossman, "Consonant co-occurrence classes and the feature-economy principle", Phonology 37 (2020)

## Statement

Take the PHOIBLE CSV at the commit above (one row per phoneme per inventory; relevant columns InventoryID, Glottocode, Phoneme, Marginal, raisedLarynxEjective; missing values are the literal string NA). Discard every row whose Marginal field is the string TRUE. An inventory "has ejectives" if at least one of its remaining rows has raisedLarynxEjective equal to "+"; it "has ng" if at least one of its remaining rows has Phoneme exactly equal to the single character U+014B (the IPA velar nasal), with no diacritics or length marks. Table A is the 2 x 2 count over all 3,020 inventories. Table B is the same count over one inventory per language: discard the one inventory whose Glottocode is NA, and for each remaining Glottocode keep only the inventory with the numerically smallest InventoryID (2,175 inventories).

## What a re-derivation must output to count

Table A: has ejectives and has ng: 39; has ejectives, no ng: 226; no ejectives, has ng: 1841; no ejectives, no ng: 914 (row totals 265 and 2755). Table B: 31; 147; 1354; 643 (row totals 178 and 1997). All eight cells are required.

## Novelty basis (as supplied)

the tables themselves are a deterministic property of the public dataset; what was not found in the literature (the WALS chapters by Maddieson and Anderson, Lee 2025, Nikolaev and Grossman 2020, Urban and Moran, PLOS One 2021, the Konstanz Universals Archive as far as it could be searched) is any statement of the association they show. The statistical interpretation of the association (family and area controls) is deliberately not part of this claim.

## Hardness (as supplied)

trivial (pandas, under a minute). The dataset must be fetched at the stated commit; later commits may change counts.

## Provenance and commitment

Supplied by the pilot's funder on 2026-09-16 (see the [index preamble](INDEX.md)). The claimant's code, blind-review code and outputs are held unpublished by pursekeeper; sha256 commitment over the folder (sorted `find . -type f | xargs sha256sum`, then sha256 of that list): `1db775a17f161d41fa01d052910c36ebc0f0b6399f0075e206ef531a6c555693`. Published here after the verdicts.
