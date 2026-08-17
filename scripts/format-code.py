import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src"


def run(command):
    subprocess.run(command, cwd=ROOT, check=True)


def source_files():
    extensions = {".cpp", ".hpp"}

    return [
        path
        for path in SRC.rglob("*")
        if path.is_file() and path.suffix in extensions
    ]


def clang_format(files):
    if not files:
        return

    run(
        [
            "clang-format",
            "-i",
            *map(str, files),
        ]
    )


def main():
    files = source_files()

    if not files:
        print("No C++ files found.")
        return

    print(f"🎨 Formatting {len(files)} C++ files...")

    clang_format(files)

    print("✅ Formatting complete.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        print(f"❌ Formatting failed with exit code {error.returncode}.")
        sys.exit(error.returncode)
