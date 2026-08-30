#!/usr/bin/env python3
"""Local interactor for CSES interactive problems 270-275.
Usage: interact.py <problem> <binary> <hidden_in_file>
Reads hidden data, drives the solution binary over pipes, validates.
"""
import sys, subprocess

def read_tokens(path):
    with open(path) as f:
        return f.read().split()

def main():
    prob = int(sys.argv[1]); binary = sys.argv[2]; hidden = sys.argv[3]
    tok = read_tokens(hidden); idx = 0
    def nxt():
        nonlocal idx; v = tok[idx]; idx += 1; return v

    p = subprocess.Popen([binary], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True, bufsize=1)
    def send(s): p.stdin.write(s + "\n"); p.stdin.flush()
    def recv(): 
        line = p.stdout.readline()
        if not line: raise RuntimeError("solution closed output unexpectedly")
        return line.strip()

    qcount = 0
    try:
        if prob == 270:
            x = int(nxt()); limit = 30
            while True:
                line = recv().split()
                if line[0] == '?':
                    qcount += 1
                    if qcount > limit: return fail("too many queries")
                    y = int(line[1]); send("YES" if y < x else "NO")
                elif line[0] == '!':
                    ok = int(line[1]) == x
                    return done(ok, qcount, f"got {line[1]} want {x}")
        elif prob == 271:
            n = int(nxt()); a = [0] + [int(nxt()) for _ in range(n)]; limit = 10**4
            send(str(n))
            while True:
                line = recv().split()
                if line[0] == '?':
                    qcount += 1
                    if qcount > limit: return fail("too many queries")
                    i, j = int(line[1]), int(line[2]); send("YES" if a[i] < a[j] else "NO")
                elif line[0] == '!':
                    guess = list(map(int, line[1:1+n])); ok = guess == a[1:]
                    return done(ok, qcount, f"mismatch")
        elif prob == 272:
            n = int(nxt()); k = int(nxt())
            F = sorted([int(nxt()) for _ in range(n)], reverse=True)
            S = sorted([int(nxt()) for _ in range(n)], reverse=True)
            allsorted = sorted(F + S, reverse=True); kth = allsorted[k-1]; limit = 100
            send(f"{n} {k}")
            while True:
                line = recv().split()
                if line[0] in ('F', 'S'):
                    qcount += 1
                    if qcount > limit: return fail("too many queries")
                    i = int(line[1]); send(str((F if line[0]=='F' else S)[i-1]))
                elif line[0] == '!':
                    ok = int(line[1]) == kth
                    return done(ok, qcount, f"got {line[1]} want {kth}")
        elif prob == 273:
            n = int(nxt()); a = [0] + [int(nxt()) for _ in range(n)]; limit = 10
            send(str(n))
            while True:
                line = recv().split()
                if line[0] == '?':
                    qcount += 1
                    if qcount > limit: return fail("too many queries")
                    b = line[1]  # b_1..b_n
                    c = ''.join(b[a[i]-1] for i in range(1, n+1))  # c_i = b_{a_i}
                    send(c)
                elif line[0] == '!':
                    guess = list(map(int, line[1:1+n])); ok = guess == a[1:]
                    return done(ok, qcount, "mismatch")
        elif prob == 274:
            n = int(nxt()); col = nxt()  # color string length n, 1-indexed via col[i-1]
            limit = 20
            send(str(n))
            while True:
                line = recv().split()
                if line[0] == '?':
                    qcount += 1
                    if qcount > limit: return fail("too many queries")
                    i = int(line[1]); send(col[i-1])
                elif line[0] == '!':
                    i = int(line[1]); j = i % n + 1
                    ok = col[i-1] == col[j-1]
                    return done(ok, qcount, f"chairs {i},{j} colors {col[i-1]},{col[j-1]}")
        elif prob == 275:
            n = int(nxt()); a = [int(nxt()) for _ in range(n)]; limit = 4 * n
            send(str(n))
            def inversions(arr):
                m = len(arr)
                comp = sorted(set(arr)); rank = {v: i+1 for i, v in enumerate(comp)}
                bit = [0]*(len(comp)+1); c = 0
                for idx2 in range(m-1, -1, -1):
                    r = rank[arr[idx2]] - 1
                    while r > 0: c += bit[r]; r -= r & -r
                    r = rank[arr[idx2]]
                    while r <= len(comp): bit[r] += 1; r += r & -r
                return c
            while True:
                line = recv().split()
                i, j = int(line[0]), int(line[1])
                qcount += 1
                if qcount > limit: return fail(f"too many ops {qcount}>{limit}")
                a[i-1:j] = a[i-1:j][::-1]
                inv = inversions(a)
                send(str(inv))
                if inv == 0:
                    # solution should terminate now
                    p.wait(timeout=5)
                    return done(True, qcount, "sorted")
    except Exception as e:
        return fail(str(e))

def done(ok, q, msg):
    print(f"{'OK' if ok else 'WA'} queries={q} {msg}")
    sys.exit(0 if ok else 1)
def fail(msg):
    print(f"FAIL {msg}"); sys.exit(1)

if __name__ == "__main__":
    main()
