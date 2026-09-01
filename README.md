# CSES

Tooling for solving [CSES Problem Set](https://cses.fi) problems in C++23:
download statements and test data, judge locally, submit, and debug in VS Code.
The repository also contains **Toy** — a compact MLIR-based language for
competitive programming — with a Toy solution for every one of the 400
problems. See `toy_lang/README.md` and `toy_lang/docs/language.md`.

## Setup

```bash
python -m venv .venv
.venv/bin/pip install -r requirements.txt
# If direct connections get reset, route through a local proxy:
export https_proxy=http://127.0.0.1:7897 http_proxy=http://127.0.0.1:7897
```

## Login

```bash
.venv/bin/python login.py -u USER -p PASS    # or CSES_USER / CSES_PASS env vars
```

Logs into cses.fi and saves the session token to `.token` (mode 600).
Re-run when the token expires (server-side session).

## Download

```bash
.venv/bin/python download.py            # index.json + per-problem metadata + statements (no login)
.venv/bin/python download.py 1068       # tests.zip for one task (needs .token)
.venv/bin/python download.py all        # tests.zip for all tasks (-j N threads)
```

Per-problem output in `problems/NNN/`: `index.json` (this problem's metadata),
`statement.md`, `tests.zip`. Existing files are skipped (resume).

## Submit

```bash
.venv/bin/python submit.py 001 005 --option C++23
```

Submits `problems/NNN/main.cpp` (see `--file`), polls until a terminal verdict,
then prints a summary; exit code 0 iff all submissions were accepted.
Requires `.token`.

## Build and test

Each `problems/NNN/main.cpp` becomes two binaries in `build/NNN/`:

- `NNN-solver` — optimized (Release)
- `NNN-solver-debug` — `-O0 -g`, for debugging

```bash
cmake --preset default                          # configure (Ninja, build/)
cmake --build build                             # build solvers + checker
cmake --build build --target mktest             # unzip all tests.zip into build/NNN/
cmake --build build --target rmtest             # remove extracted tests
cmake --build build --target judge              # solve every .in and check with checker
ctest --test-dir build                          # one registered test per input file
```

`judge` runs `NNN-solver < t.in > t.tmp`, then `checker t.in t.tmp t.out`
(verdict written to `build/NNN/t.res`). A per-problem `problems/NNN/checker.cpp`
overrides the shared `checker/checker.cpp` (testlib).

## Toy language

Every `problems/NNN/main.toy` compiles to a native executable and is judged
against the same test data as `main.cpp`:

```bash
cmake --build build --target toy-build-NNN    # compile one Toy solution
cmake --build build --target toy-judge-NNN    # run all tests for problem NNN
cmake --build build --target toy-judge        # run all 400 problems
```

Interactive problems 270-275 are judged through `tools/interact.py`.
Solutions run under a 512 MiB / 300 s guard (`tools/toy_guard.py`).

## VS Code debugging

Use the CMake Tools extension with the `default` preset
(`compile_flags.txt` provides clangd with the right flags), then create a
launch configuration that runs `NNN-solver-debug` and feeds a failing input
as stdin:

```json
{
    "name": "cses debug",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/build/001/001-solver-debug",
    "cwd": "${workspaceFolder}",
    "stdin": "${workspaceFolder}/build/001/t.in",
    "MIMode": "gdb"
}
```

## Interactive problems

`tools/interact.py` drives solution binaries against hidden inputs for the
interactive problems (270-275):

```bash
.venv/bin/python tools/interact.py <problem> <binary> <hidden_in_file>
```

## Layout

    login.py / download.py / submit.py   Python tooling (token in .token)
    problems/NNN/                        main.cpp, optional checker.cpp,
                                         index.json, statement.md, tests.zip
    checker/                             shared checker (testlib)
    tools/                               interactive problem runner
    build/                               CMake build + extracted tests (ignored)
