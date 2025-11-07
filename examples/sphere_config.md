# Sphere benchmark: background, settings, and visuals

This note explains the **Sphere** objective used in the repository example and provides quick,
practical guidance (bounds and parameters), plus visuals you can include in the README or docs.

## What is the Sphere function?
The Sphere function in R^d is defined as:
\[
\operatorname{Sphere}(\mathbf{x}) = \sum_{i=1}^{d} x_i^2
\]
It is **convex**, **separable**, and **strictly unimodal** with a unique global minimum at
\(\mathbf{x}^* = \mathbf{0}\) where \(f(\mathbf{x}^*) = 0\). Because of its smooth, bowl-shaped
landscape, it is commonly used to **sanity-check** the behavior of optimizers such as PSO.

**Why Sphere is useful here**
- Ensures the implementation moves downhill consistently.
- Highlights how **personal bests** and the **global best** guide the swarm.
- Shows typical PSO behavior: quick coarse approach to the basin, then fine convergence near the origin.

## Recommended bounds and defaults
- **Position bounds** (example): `X_MIN = -5.12`, `X_MAX = 5.12`
- **Velocity bounds** (example): `V_MIN = -10`, `V_MAX = 10`
- **Swarm size**: `P = 10`–`30` for low dimensions (e.g., `d=3`); higher for larger `d`
- **Iterations**: `100`–`500` for quick tests
- **Topology**: global-best
- **Heuristics**: consider decreasing inertia `w` over time (exploration → exploitation)

> Tip: For higher dimensions (e.g., `d=10`), increase `P` and `max_iter` to maintain reliable convergence.

## Visuals (add to your repo)
Place the images below in your repository (for example under `docs/`) and reference them in the README or here.

- 3D surface (2D slice of Sphere):  
  ![Sphere surface](PSO-in-C-for-continuous-optimization/docs/sphere_surface.png)

- 2D contour view:  
  ![Sphere contours](PSO-in-C-for-continuous-optimization/docs/sphere_contours.png)

> If you use a different folder, update the relative paths accordingly.

## How PSO converges on Sphere (interpretation guide)
- Each particle keeps track of its **personal best** `p_i` and is attracted toward the **global best** `g`.
- The velocity update includes: **inertia** (momentum), **cognitive** pull (toward `p_i`), and **social** pull (toward `g`).
- You should see **best fitness** decrease rapidly at first as the swarm reaches the basin around the origin, then more slowly as it fine-tunes.

**What to look for in your run output**
- A monotonic (or near-monotonic) decline in the reported **best fitness**.
- Final **best position** numerically close to the zero vector.
- Stable behavior (no explosions): if positions/velocities saturate at bounds too often, revisit limits or inertia.

## Add your results here
Paste the key excerpts of your run (e.g., iteration blocks or final summary). We can then add a short narrative like:
> “Early iterations show the swarm fanning out within the bounds, then converging as the global best stabilizes. By iteration ~N, most particles orbit a tight region around `g`, and the global best position is within ε of the origin, yielding a best fitness near 0.”

### Optional: convergence plot
If you export a per-iteration `best_fitness` CSV, you can plot it with a simple script (e.g., `scripts/plot_convergence.py`). A typical curve on Sphere is a smooth descending line that flattens near zero.

