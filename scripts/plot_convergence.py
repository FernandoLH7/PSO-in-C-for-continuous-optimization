#!/usr/bin/env python3
"""
plot_convergence.py
Plot PSO convergence for the Sphere function WITHOUT needing a CSV.
Hard-coded points taken from the console output shown by the user.

Usage (from repo root):
    python3 scripts/plot_convergence.py --out docs/convergence.png --title "PSO Convergence (Sphere)"
    # Optional (log scale):
    python3 scripts/plot_convergence.py --out docs/convergence_log.png --log10

Edit the POINTS list below if you have new runs.
"""

import os
import argparse
import math
import matplotlib.pyplot as plt

# ---- Hard-coded convergence data (iter, best_fitness) ----
POINTS = [
    (0, 9.8740),
    (10, 0.5699),   # si tu log mostró un negativo por formato, lo corregimos a positivo
    (20, 0.1666),
    (30, 0.0017),
    (40, 0.0017),
    (50, 0.0008),
    (60, 0.0008),
    (70, 0.0003),
    (80, 0.0003),
    (90, 0.0002),
    (99, 0.0001),
]
# ----------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description="Plot PSO convergence from hard-coded data (no CSV).")
    ap.add_argument("--out", default="docs/convergence.png", help="Output image path")
    ap.add_argument("--title", default="PSO Convergence (Sphere)", help="Plot title")
    ap.add_argument("--log10", action="store_true", help="Use log10(best_fitness) on Y axis")
    args = ap.parse_args()

    iters = [i for i, _ in POINTS]
    vals = [max(v, 1e-16) for _, v in POINTS]  # clamp to avoid log of non-positive

    y = [math.log10(v) for v in vals] if args.log10 else vals
    ylabel = "log10(best_fitness)" if args.log10 else "Best fitness"

    plt.figure()
    plt.plot(iters, y, marker="o")
    plt.xlabel("Iteration")
    plt.ylabel(ylabel)
    plt.title(args.title)
    plt.grid(True)
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    plt.tight_layout()
    plt.savefig(args.out, dpi=180)
    print(f"Saved {args.out}")

if __name__ == "__main__":
    main()

