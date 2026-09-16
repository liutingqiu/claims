# Sandbox runs

One directory per run of a submitted re-derivation: `<UTC stamp>-<label>/` with `run.log`
(stdout and stderr of the submission's `run.sh`), `meta.json` (exit code, wall seconds,
limits, image, sha256 commitment over the submitted files) and `files.sha256`. The
submitted files themselves are in the reviewer's own repository or attachment; `work/`
is not committed here. Runs are pushed after each verdict.
