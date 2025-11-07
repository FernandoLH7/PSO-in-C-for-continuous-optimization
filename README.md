# PSO-in-C-for-continuous-optimization
Clean Particle Swarm Optimization (PSO) in C, with a worked example on the Sphere function (minimization). Global-best variant, position/velocity bounds, and reproducible baseline suitable for coursework, research prototypes, or industry experiments.

# Particle Swarm Optimization (PSO) in C — Sphere Minimization

This repository provides a **clear, compact implementation** of Particle Swarm Optimization (PSO) in **C** with a worked example on the **Sphere** function:
\[
\text{Sphere}(x) = \sum_{i=1}^{R} x_i^2 \quad (\text{global minimum at } x = 0)
\]

The code uses a **global-best** PSO:
- Inertia term `w`
- Cognitive and social terms `c1` and `c2`
- Position and velocity clamping to predefined bounds

> Baseline settings are easy to adjust via macros (`P`, `R`, `X_MIN`, `X_MAX`, `V_MIN`, `V_MAX`, etc.).

---

## How PSO updates work (quick refresher)

Velocity and position updates follow the classical form:
\[
v_{i}(t{+}1)= w\,v_{i}(t) + c_1 r_1\,[p_{i}(t)-x_{i}(t)] + c_2 r_2\,[g(t)-x_{i}(t)]
\]
\[
x_{i}(t{+}1)=x_{i}(t)+v_{i}(t{+}1)
\]

Where:
- \(p_i\) is the particle’s personal best,
- \(g\) is the global best,
- \(r_1, r_2 \sim U(0,1)\).

---

## Build & Run

Requirements: **gcc** or **clang** (Linux/macOS).  
> The code uses `drand48/srand48` for RNG. See **Windows notes** below.

```bash
# Build
gcc -O2 -Wall -Wextra -o pso src/pso.c

# Run
./pso

