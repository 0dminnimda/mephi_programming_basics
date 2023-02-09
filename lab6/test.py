from __future__ import annotations

import random
import re
import shlex
import string
import subprocess
import sys
from dataclasses import dataclass
from difflib import unified_diff
from pathlib import Path
from typing import List


@dataclass
class Shell:
    return_code: int = 0
    stdout: str | None = None

    def update(self, return_code: int = 0, stdout: str | None = None) -> Shell:
        self.return_code = return_code
        self.stdout = stdout
        return self

    @property
    def output(self) -> str:
        return self.stdout or ""

    def run(
        self, command: str, capture: bool = False, timeout: int | None = None
    ) -> Shell:
        kwargs = {}
        if capture:
            kwargs["stdout"] = subprocess.PIPE
            kwargs["stderr"] = subprocess.STDOUT

        completed = subprocess.run(
            shlex.split(command),
            input=self.output,
            timeout=timeout,
            encoding="utf-8",
            text=True,
            # shell=True,
            **kwargs,
        )
        return self.update(completed.returncode, completed.stdout)

    def pipe(self, command: str, timeout: int | None = None) -> Shell:
        return self.run(command, capture=True, timeout=timeout)

    def input(self, data: str) -> Shell:
        return self.update(stdout=data)


def random_string(
    min_len: int = 5,
    max_len: int = 25,
    alphabet: str = string.digits + string.ascii_letters + " \t",
) -> str:
    return "".join(
        random.choice(alphabet) for _ in range(random.randint(min_len, max_len))
    )


def create_tests() -> List[str]:
    random.seed(42)

    tests = []
    tests.append("")
    for _ in range(50):
        tests.append((random_string(1, 50) + " ") * random.randint(1, 5))

    return tests


def run(tests: List[str], override: bool = False) -> None:
    shell = Shell()

    print("Building the program")
    shell.run("./build.sh")

    all_output = shell.input("\n".join(tests)).pipe("./main").output

    output_file = Path("test.output")
    if override or not output_file.exists():
        output_file.write_text(all_output, "utf-8")
    else:
        output = output_file.read_text("utf-8")
        if output != all_output:
            print("Test output differs with a recorded one:")
            print("\n".join(unified_diff(output.split("\n"), all_output.split("\n"))))


def main(in_argv: List[str] = sys.argv) -> None:
    tests = create_tests()

    argv = dict(enumerate(in_argv))
    if argv.get(1) == "make_cases":
        with open(argv.get(2, "test_cases.txt"), "w", encoding="utf-8") as f:
            f.write("\n".join(tests))
        exit()

    run(tests, argv.get(1) == "override")


if __name__ == "__main__":
    main()
