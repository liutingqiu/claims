#!/usr/bin/env python3
# Regenerates claims/INDEX.md from claims/index.json. Run after every verdict.
import json
idx=json.load(open('claims/index.json'))
out=["# Index of claims","",
"Seventeen seed claims supplied by the pilot's funder on 2026-09-16 (provenance: supplied by the pilot funder; prior work cited by author and title; the people who produced the claims are not identified; all produced by exhaustive computation on 16 September 2026). Claims are independent of each other. Every claim can be checked by running code; the pass criterion is term by term, no tolerances.",
"",
"Conventions: a *free polyomino* is a finite edge-connected set of unit squares of the square grid, counted up to translations, rotations and reflections, holes allowed (OEIS A000105). The *cell graph* of a polyomino has one vertex per cell and an edge between two cells that share a side.",
"",
"For every accepted claim the field tags, the keywords and the one-line *verified* entry below are kept so that a researcher scanning for checked small results can find them. The same data is in [`index.json`](index.json).",
"",
"| # | Claim | Field tags | Status | Issue | Reviews accepted | Verified (what, how) |","|---|---|---|---|---|---|---|"]
for c in idx:
    issue=f"[#{c['issue']['number']}]({c['issue']['url']})" if c.get('issue') else ""
    rev=", ".join(f"{r['by']} ({r['verdict']}, {r['range']})" for r in c.get('reviews',[])) or ""
    ver=c.get('verified') or ""
    out.append(f"| {c['n']} | [{c['title']}]({c['file'].split('/',1)[1]}) | {', '.join(c['field_tags'])} | {c['status']} | {issue} | {rev} | {ver} |")
out+=["","## Keywords","",]
for c in idx: out.append(f"- **{c['n']}** {', '.join(c['keywords'])}")
out+=["","## Prior art reported","",]
pa=[(c['n'],p) for c in idx for p in c.get('prior_art',[])]
out+= [f"- claim {n}: {p['url']} ({p['by']}, {p['verdict']})" for n,p in pa] or ["- none yet"]
open('claims/INDEX.md','w').write("\n".join(out)+"\n")
print("INDEX.md", len(idx), "claims")
