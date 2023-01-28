from __future__ import annotations

import sys
import random
import re
import shlex
import string
import subprocess
from dataclasses import dataclass
from typing import List, Tuple


@dataclass
class Shell:
    return_code: int = 0
    stdout: str | None = None
    stderr: str | None = None

    def update(
        self, return_code: int = 0, stdout: str | None = None, stderr: str | None = None
    ) -> Shell:
        self.return_code = return_code
        self.stdout = stdout
        self.stderr = stderr
        return self

    @property
    def output(self) -> str:
        return self.stdout or self.stderr or ""

    def run(self, command: str, use_stdout: bool = True) -> Shell:
        completed = subprocess.run(
            shlex.split(command),
            input=self.output,
            capture_output=not use_stdout,
            encoding="utf-8",
            text=True,
            # shell=True,
        )
        return self.update(completed.returncode, completed.stdout, completed.stderr)

    def pipe(self, command: str) -> Shell:
        return self.run(command, use_stdout=False)

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


def make_a_s(n: int) -> str:
    return " ".join(("a" * i for i in range(1, n + 1)))


def create_cases() -> str:
    random.seed(42)

    cases = "asdas sad  fff fff ff f   fghjhg\n"
    cases += "\n"
    cases += make_a_s(8) + "\n"
    cases += make_a_s(30) + "\n"
    cases += make_a_s(100) + "\n"
    cases += make_a_s(400) + "\n"
    for _ in range(50):
        cases += (random_string(1, 50) + " ") * random.randint(1, 5) + "\n"

    return cases + "=)"


def run(cases: str) -> Tuple[str, str]:
    shell = Shell()

    print("===================")
    print("= Custom readline =")
    print("===================")

    shell.run("./build.sh")
    out1 = shell.input(cases).pipe("./main").output
    # print(out1)

    print("================")
    print("= GNU readline =")
    print("================")

    shell.run("./build.sh 1")
    out2 = shell.input(cases).pipe("./main").output
    # print(out2)

    return out1, out2


def show_results(out1, out2):
    inputs = re.findall(r'Words found: "(.*)"', out1)
    results1 = re.findall(r"Total: (\d+\.\d+) seconds", out1)
    results2 = re.findall(r"Total: (\d+\.\d+) seconds", out2)

    ratios = [float(res2) / float(res1) for res1, res2 in zip(results1, results2)]

    print("Average gnu to custom time ratio:", sum(ratios) / len(ratios))
    print("Minimum gnu to custom time ratio:", min(ratios))
    print("Maximum gnu to custom time ratio:", max(ratios))

    str_cut = 50
    time_cut = max(len(results1[0]), len(results2[0]), len("Custom time"))
    line = "{: <{str_cut}}{} - {: <{time_cut}} {: <{time_cut}} - {}"

    print(
        line.format(
            f"\nInput (first {str_cut} characters)",
            "    ",
            "Custom time",
            "Gnu time",
            "Gnu to custom ratio",
            **locals(),
        )
    )

    for inp, res1, res2, ratio in zip(inputs, results1, results2, ratios):
        print(line.format(inp[:str_cut], "...", res1, res2, ratio, **locals()))


def main(in_argv: List[str] = sys.argv):
    cases = create_cases()

    argv = dict(enumerate(in_argv))
    if argv.get(1) == "make_cases":
        with open(argv.get(2, "test_cases.txt"), "w", encoding="utf-8") as f:
            f.write(cases)
        exit()

    show_results(*run(cases))


if __name__ == "__main__":
    main()
