#!/usr/bin/env python3
"""Run one evaluation command under memory and CPU limits.

Usage:
    toy_guard.py --memory-mb N [--time-seconds N] -- command args...

The limits are applied with setrlimit in the child (RLIMIT_AS for address
space, RLIMIT_CPU for CPU time), so no cgroups or root privileges are needed.
If the child is killed by a signal, the wrapper exits with 128 + signal.
"""

import argparse
import os
import resource
import shutil
import subprocess
import sys


def main() -> int:
    parser = argparse.ArgumentParser(description="run a command under rlimits")
    parser.add_argument("--memory-mb", type=int, required=True, help="address-space limit in MiB")
    parser.add_argument("--time-seconds", type=int, default=300, help="CPU time limit in seconds")
    parser.add_argument("command", nargs=argparse.REMAINDER, help="command and arguments after '--'")
    arguments = parser.parse_args()

    command = arguments.command
    if command and command[0] == "--":
        command = command[1:]
    if not command:
        print("toy_guard: no command given", file=sys.stderr)
        return 2

    # CMake runs custom commands with the build directory on PATH, but Python's
    # subprocess only searches PATH.  Resolve a bare executable name against the
    # current directory as well so `checker`-style invocations keep working.
    executable = command[0]
    if "/" not in executable and shutil.which(executable) is None and os.path.exists(executable):
        command = [os.path.abspath(executable)] + command[1:]

    memory_limit = arguments.memory_mb * 1024 * 1024
    time_limit = arguments.time_seconds

    def apply_limits() -> None:
        resource.setrlimit(resource.RLIMIT_AS, (memory_limit, memory_limit))
        resource.setrlimit(resource.RLIMIT_CPU, (time_limit, time_limit + 10))

    try:
        process = subprocess.run(command, preexec_fn=apply_limits)
    except FileNotFoundError:
        print(f"toy_guard: command not found: {command[0]}", file=sys.stderr)
        return 127

    if process.returncode < 0:
        signal_number = -process.returncode
        print(
            f"toy_guard: killed by signal {signal_number} "
            f"(memory limit {arguments.memory_mb}MiB, cpu limit {time_limit}s)",
            file=sys.stderr,
        )
        return 128 + signal_number
    return process.returncode


if __name__ == "__main__":
    sys.exit(main())
