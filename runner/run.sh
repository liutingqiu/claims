#!/usr/bin/env bash
# Sandboxed run of a re-derivation submission.
#   run.sh <submission_dir> <label>
# The submission must contain a top-level run.sh that builds and runs everything and prints its result.
# Sandbox: Docker image pursekeeper/rederive:v0 (Ubuntu 24.04, gcc/g++, python3 + sympy gmpy2 pandas numpy networkx scipy),
# no network, 2 CPUs, 4 GB RAM, 256 processes, 10 minutes wall clock, /data read-only with the pinned datasets.
# Output: runs/<stamp>-<label>/{run.log,meta.json,work/}. Everything under runs/ is published after the verdict.
set -u
SUB=${1:?submission dir}; LABEL=${2:?label}
HERE=$(cd "$(dirname "$0")/.." && pwd)
STAMP=$(date -u +%Y%m%dT%H%M%SZ)
RUNS_DIR=${RUNS_DIR:-$HERE/runs}; RUN="$RUNS_DIR/$STAMP-$LABEL"; mkdir -p "$RUN/work"
cp -r "$SUB"/. "$RUN/work/"
chmod -R a+rwX "$RUN/work"
# commitment: sha256 over the submitted files (sorted paths, contents)
( cd "$RUN/work" && find . -type f | sort | xargs sha256sum ) > "$RUN/files.sha256"
SHA=$(sha256sum "$RUN/files.sha256" | cut -c1-64)
[ -f "$RUN/work/run.sh" ] || { echo "no run.sh at top level" | tee "$RUN/run.log"; exit 2; }
START=$(date +%s)
timeout -k 10 600 docker run --rm --name "rederive-$STAMP-$LABEL" \
  --network none --cpus 2 --memory 4g --memory-swap 4g --pids-limit 256 \
  -v "$RUN/work":/work -v "$HERE/fixtures":/data:ro \
  pursekeeper/rederive:v0 bash -c 'cd /work && bash run.sh' > "$RUN/run.log" 2>&1
RC=$?
END=$(date +%s)
docker rm -f "rederive-$STAMP-$LABEL" >/dev/null 2>&1 || true
python3 - "$RUN" "$LABEL" "$SHA" "$RC" "$((END-START))" "$STAMP" <<'PY'
import json,sys
run,label,sha,rc,secs,stamp=sys.argv[1:]
json.dump({'label':label,'stamp':stamp,'submission_sha256':sha,'exit_code':int(rc),'wall_seconds':int(secs),
  'limits':{'wall_seconds':600,'cpus':2,'memory':'4g','network':'none'},'image':'pursekeeper/rederive:v0'},
  open(run+'/meta.json','w'),indent=1)
PY
echo "run: $RUN"; echo "exit $RC after $((END-START))s; sha256 $SHA"; tail -n 20 "$RUN/run.log"
