#!/usr/bin/env python3
"""One-shot deterministic rename of the CML prototype to the Toy language.

Run once from the repository root. It is safe to delete afterwards.
"""

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

FILE_RENAMES = [
    ("compiler/cmlc.py", "compiler/toyc.py"),
    ("include/CML", "include/Toy"),
    ("include/Toy/CMLDialect.td", "include/Toy/ToyDialect.td"),
    ("include/Toy/CMLOps.td", "include/Toy/ToyOps.td"),
    ("include/Toy/CMLPasses.td", "include/Toy/ToyPasses.td"),
    ("include/Toy/CMLDialect.h", "include/Toy/ToyDialect.h"),
    ("include/Toy/CMLOps.h", "include/Toy/ToyOps.h"),
    ("include/Toy/CMLPasses.h", "include/Toy/ToyPasses.h"),
    ("lib/CMLDialect.cpp", "lib/ToyDialect.cpp"),
    ("lib/CMLPasses.cpp", "lib/ToyPasses.cpp"),
    ("lib/prelude.mlir", "lib/prelude.toy"),
    ("runtime/cml_runtime.c", "runtime/toy_runtime.c"),
    ("runtime/cml_heap.c", "runtime/toy_heap.c"),
    ("runtime/cml_ordered.c", "runtime/toy_ordered.c"),
    ("tools/cml-opt", "tools/toy-opt"),
    ("tools/toy-opt/cml-opt.cpp", "tools/toy-opt/toy-opt.cpp"),
]

TEXT_REPLACEMENTS = [
    ("CMLC", "TOYC"),
    ("CmlError", "ToyError"),
    ("CML", "Toy"),
    ("cml", "toy"),
    ("prelude.mlir", "prelude.toy"),
    ("main.mlir", "main.toy"),
]


def rewrite(path: Path) -> None:
    original = path.read_text(encoding="utf-8")
    changed = original
    for old, new in TEXT_REPLACEMENTS:
        changed = changed.replace(old, new)
    if changed != original:
        path.write_text(changed, encoding="utf-8")


def main() -> None:
    for old, new in FILE_RENAMES:
        source = ROOT / old
        if source.exists():
            source.rename(ROOT / new)

    for path in sorted(ROOT.rglob("*")):
        if path.is_file() and path.suffix in {".py", ".td", ".h", ".cpp", ".c", ".toy", ".md", ".txt"}:
            if "rename_cml_to_toy" not in path.name:
                rewrite(path)


if __name__ == "__main__":
    main()
