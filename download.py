#!/usr/bin/env python3
"""CSES downloader: statements (no login) + test data (requires .token from login.py).

Usage:
  download.py             index.json + per-problem metadata + all statements
  download.py <task_id>   tests.zip for one task
  download.py all         tests.zip for all tasks

Multithreaded (-j, default 32); existing files are skipped (resume).
Set https_proxy first if direct connection is blocked.
"""
import argparse
import json
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup
from markdownify import markdownify

BASE = "https://cses.fi"
OUT = Path(__file__).resolve().parent / "problems"
TOKEN = Path(__file__).resolve().parent / ".token"


def session(token: str = "") -> requests.Session:
    """New session, optionally with a cookie (bare PHPSESSID or 'k=v; ...')."""
    s = requests.Session()
    if token:
        if "=" in token:
            for part in token.split(";"):
                k, _, v = part.partition("=")
                if k.strip():
                    s.cookies.set(k.strip(), v, domain=".cses.fi")
        else:
            s.cookies.set("PHPSESSID", token, domain=".cses.fi")
    return s


def problems() -> list[dict]:
    """Parse the problemset page in display order (h2 = section, a = task)."""
    soup = BeautifulSoup(session().get(BASE + "/problemset/", timeout=30).text, "html.parser")
    out, section, idx = [], "Unknown", 0
    for el in (soup.find("div", class_="content") or soup).find_all(["h2", "a"]):
        if el.name == "h2":
            section = el.get_text(strip=True)
            continue
        m = re.match(r"^/problemset/task/(\d+)/?$", el.get("href", ""))
        title = el.get_text(strip=True)
        if m and title and title.upper() not in {"TASK", "STATISTICS"}:
            idx += 1
            out.append({"idx": idx, "task_id": int(m.group(1)), "title": title, "section": section})
    return out


def statement(p: dict) -> None:
    """Fetch one statement as Markdown into problems/NNN/statement.md."""
    f = OUT / f"{p['idx']:03d}" / "statement.md"
    if f.exists() and f.stat().st_size > 0:
        return
    soup = BeautifulSoup(session().get(f"{BASE}/problemset/task/{p['task_id']}", timeout=30).text,
                         "html.parser")
    main = soup.find("div", class_="md") or soup.find("div", class_="content") or soup
    md = re.sub(r"\n{3,}", "\n\n", markdownify(str(main), heading_style="ATX", bullets="-")).strip() + "\n"
    f.parent.mkdir(parents=True, exist_ok=True)
    f.write_text(md, encoding="utf-8")
    print(f"[{p['idx']:03d}] {p['title']} ok", flush=True)


def tests(p: dict, token: str) -> None:
    """Fetch tests.zip via the page's POST form into problems/NNN/tests.zip."""
    f = OUT / f"{p['idx']:03d}" / "tests.zip"
    if f.exists() and f.stat().st_size > 0:
        return
    s = session(token)
    page = s.get(f"{BASE}/problemset/tests/{p['task_id']}/", timeout=30)
    if page.status_code != 200:  # 404 when not logged in
        print(f"[{p['idx']:03d}] {p['title']}: not logged in (token expired?)", flush=True)
        return
    form = BeautifulSoup(page.text, "html.parser").find("form")
    if form is None:
        print(f"[{p['idx']:03d}] {p['title']}: no data", flush=True)
        return
    data = {i.get("name"): i.get("value", "") for i in form.find_all("input") if i.get("name")}
    r = s.post(urljoin(page.url, form.get("action") or ""), data=data, timeout=60)
    if "html" in r.headers.get("Content-Type", "").lower():
        print(f"[{p['idx']:03d}] {p['title']}: no data", flush=True)
        return
    f.parent.mkdir(parents=True, exist_ok=True)
    f.write_bytes(r.content)
    print(f"[{p['idx']:03d}] {p['title']}: {len(r.content)}B ok", flush=True)


def run(fn, p: dict, *args) -> None:
    """Run fn(p) and keep going on network errors."""
    try:
        fn(p, *args)
    except requests.RequestException as e:
        print(f"[{p['idx']:03d}] {p['title']} FAIL {e}", flush=True)


def main() -> None:
    ap = argparse.ArgumentParser(description="CSES downloader")
    ap.add_argument("target", nargs="?", default="",
                    help="task id or 'all'; default = index.json + all statements")
    ap.add_argument("-j", "--threads", type=int, default=32, help="threads (default 32)")
    args = ap.parse_args()

    token = ""
    if args.target:
        if not TOKEN.exists():
            sys.exit("No .token found: run login.py first")
        token = TOKEN.read_text().strip()

    ps = problems()
    if not ps:
        sys.exit("Failed to fetch problem list")

    if not args.target:  # mode 1: metadata + all statements
        OUT.mkdir(parents=True, exist_ok=True)
        (OUT / "index.json").write_text(json.dumps(ps, ensure_ascii=False, indent=2), encoding="utf-8")
        for p in ps:  # per-problem metadata copy for quick reference
            d = OUT / f"{p['idx']:03d}"
            d.mkdir(parents=True, exist_ok=True)
            (d / "index.json").write_text(json.dumps(p, ensure_ascii=False, indent=2), encoding="utf-8")
        with ThreadPoolExecutor(max_workers=args.threads) as ex:
            list(ex.map(lambda p: run(statement, p), ps))
        print(f"Done: {len(ps)} problems, index.json updated", flush=True)
        return

    if args.target == "all":  # mode 2/3: test data
        targets = ps
    else:
        try:
            tid = int(args.target)
        except ValueError:
            sys.exit(f"Invalid target: {args.target} (expect a task id number or 'all')")
        targets = [p for p in ps if p["task_id"] == tid]
        if not targets:
            sys.exit(f"Task id {tid} not found")
    with ThreadPoolExecutor(max_workers=args.threads) as ex:
        list(ex.map(lambda p: run(tests, p, token), targets))
    print("Done (existing files skipped)", flush=True)


if __name__ == "__main__":
    main()
