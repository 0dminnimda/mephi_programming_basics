from __future__ import annotations

import sys
import re
import shlex
import subprocess
from dataclasses import dataclass
from typing import List
from pathlib import Path
from difflib import unified_diff


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


IN_FILE = "sample.txt"
OUT_FILE = "out.txt"


def create_tests() -> List[str]:
    program = "./main "
    in_out_files = f"{IN_FILE} {OUT_FILE}"
    output = f"cat {OUT_FILE}"

    return [
        f"cat {IN_FILE}",
        f"{program} -h",
        f"{program} {in_out_files}",
        f"{program} {in_out_files} -w -f age -s B",
        output,
        f"{program} {in_out_files} -w -f age -s D",
        output,
        f"{program} {in_out_files} -w -f age -s Q",
        output,
        f"{program} {in_out_files} -w -f name -s B",
        output,
        f"{program} {in_out_files} -w -f name -s D",
        output,
        f"{program} {in_out_files} -w -f name -s Q",
        output,
        f"{program} {in_out_files} -w -f station -s B",
        output,
        f"{program} {in_out_files} -w -f station -s D",
        output,
        f"{program} {in_out_files} -w -f station -s Q",
        output,
    ]


def run(tests: List[str], override: bool = False) -> None:
    shell = Shell()

    all_output = ""

    print("Building the program")
    shell.run("./build.sh 1")
    for test in tests:
        print(f"Running {test}")
        all_output += f"\nRunning $ {test}\n"
        all_output += shell.pipe(test).output

    output_file = Path("test.output")
    if override or not output_file.exists():
        output_file.write_text(all_output, "utf-8")
    else:
        output = output_file.read_text("utf-8")
        if output != all_output:
            print("Test output differs with a recorded one:")
            print("\n".join(unified_diff(output.split("\n"), all_output.split("\n"))))


def get_results(iterations, lengths, sorts):
    results = Path("oo.txt")
    if results.exists():
        lines = results.read_text("utf-8").split("\n")
        for sort in sorts:
            averages = eval(f"[{lines.pop(0)}]")
            yield lengths[: len(averages)], averages, sort
        return

    shell = Shell()
    shell.pipe("./build.sh")
    program = "./main"

    average_pattern = re.compile(r"On average (\d+\.\d+)")

    text = ""
    for sort in sorts:
        averages = []
        postfix = f"{iterations} -s {sort} -f age"
        for length in lengths:
            command = f"{program} {length} {postfix}"
            print(command, end="\r")
            try:
                output = shell.pipe(command, timeout=150).output
            except subprocess.TimeoutExpired:
                break
            print(" " * (len(command) + 1), end="\r")
            averages.append(average_pattern.findall(output)[0])

        text += ", ".join(averages) + "\n"
        yield lengths[: len(averages)], [float(i) for i in averages], sort

    print()
    results.write_text(text, "utf-8")


def show_results() -> None:
    from matplotlib import pyplot as plt

    iterations = 1000
    lengths = [2**i for i in range(20)]
    sorts = "BDQ"
    names = {"B": "Bubble sort", "D": "Double selection sort", "Q": "Quick sort"}

    fig, ax = plt.subplots()
    for lengths, averages, sort in get_results(iterations, lengths, sorts):
        ax.plot(lengths, [i * 1000 for i in averages], label=names[sort])

    ax.set_xlim(0, 2**13)
    ax.set_ylim(0, 15)
    ax.set_xlabel("Array Length")
    ax.set_ylabel(f"Average Time On {iterations} Iterations (ms)")
    ax.legend()
    ax.grid(True)

    fig.tight_layout()
    fig.savefig("figure.png")


def main(in_argv: List[str] = sys.argv) -> None:
    tests = create_tests()

    argv = dict(enumerate(in_argv))
    if argv.get(1) == "make_cases":
        with open(argv.get(2, "test_cases.txt"), "w", encoding="utf-8") as f:
            f.write("\n".join(tests))
        exit()

    run(tests, argv.get(1) == "override")
    show_results()


if __name__ == "__main__":
    main()
