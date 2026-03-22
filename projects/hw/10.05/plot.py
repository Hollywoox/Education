import argparse
import csv
import sys
from pathlib import Path
import matplotlib.pyplot as plt


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", nargs="?", default=".", type=Path)
    args = parser.parse_args()

    directory = args.dir.resolve()

    csv_files = sorted(directory.glob("*.csv"))

    for path in csv_files:
        stem = path.stem
        try:
            with path.open(newline="") as f:
                rows = list(csv.DictReader(f))
        except Exception as e:
            print(f"Skip {path.name}: {e}", file=sys.stderr)
            continue

        n_vals = [int(r["N"]) for r in rows]
        collisions = [int(r["collisions"]) for r in rows]

        fig, ax = plt.subplots(figsize=(8, 6))
        ax.plot(n_vals, collisions, "o-", markersize=4)
        ax.set_xlabel("N")
        ax.set_ylabel("number of collisions")
        ax.set_title(stem)
        ax.grid(True)
        fig.tight_layout()

        out_path = directory / f"{stem}.png"
        fig.savefig(out_path, dpi=100)
        plt.close(fig)


if __name__ == "__main__":
    main()
