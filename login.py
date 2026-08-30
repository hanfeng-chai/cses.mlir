#!/usr/bin/env python3
"""Log into CSES and save the session token to .token.

Usage:
  login.py [-u USER] [-p PASSWORD]   (env CSES_USER / CSES_PASS, then prompt)
"""
import argparse
import getpass
import os
import sys
from pathlib import Path
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup

BASE = "https://cses.fi"
TOKEN = Path(__file__).resolve().parent / ".token"


def main() -> None:
    ap = argparse.ArgumentParser(description="CSES login")
    ap.add_argument("-u", "--user", default=os.environ.get("CSES_USER", ""), help="CSES username")
    ap.add_argument("-p", "--password", default=os.environ.get("CSES_PASS", ""), help="CSES password")
    args = ap.parse_args()
    user = args.user or input("Username: ")
    pw = args.password or getpass.getpass("Password: ")

    s = requests.Session()
    # The login form carries a csrf_token; fetch it first, then POST.
    soup = BeautifulSoup(s.get(BASE + "/login", timeout=30).text, "html.parser")
    form = soup.find("form")
    nick = form and form.find("input", type="text")
    pwd = form and form.find("input", type="password")
    if not (form and nick and pwd):
        sys.exit("Login failed: unexpected login page structure")
    data = {i.get("name"): i.get("value", "") for i in form.find_all("input") if i.get("name")}
    data[nick["name"]], data[pwd["name"]] = user, pw
    r = s.post(urljoin(BASE + "/login", form.get("action") or ""), data=data, timeout=30)
    if r.url.rstrip("/") == BASE + "/login":  # success redirects away from /login
        sys.exit("Login failed: invalid username or password")
    TOKEN.write_text(s.cookies.get("PHPSESSID", ""))
    TOKEN.chmod(0o600)
    print(f"Logged in as {user}; token saved to {TOKEN.name}")


if __name__ == "__main__":
    main()
