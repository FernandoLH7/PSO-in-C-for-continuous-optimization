# Sphere benchmark: background, settings, and visuals

This note explains the **Sphere** objective used in the repository example and provides quick,
practical guidance (bounds and parameters), plus visuals you can include in the README or docs.

> **Tip:** On GitHub, math is rendered using `$...$` for inline and `$$...$$` for display.
> Ensure this file is **not** inside a code block (no triple backticks around the whole section).

## What is the Sphere function?
The Sphere function in $\mathbb{R}^d$ is defined as:
$$
\operatorname{Sphere}(\mathbf{x}) = \sum_{i=1}^{d} x_i^2
$$
It is **convex**, **separable**, and **strictly unimodal** with a unique global minimum at
$\mathbf{x}^* = \mathbf{0}$ where $f(\mathbf{x}^*) = 0$. Because of its smooth, bowl-shaped
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

> For higher dimensions (e.g., $d=10$), increase `P` and `max_iter` to maintain reliable convergence.

## Visuals (add to your repo)
Place the images below under `docs/` and reference them like this:

- 3D surface (2D slice of Sphere):  
  ![Sphere surface](../docs/sphere_surface.png)

- 2D contour view:  
  ![Sphere contours](../docs/sphere_contours.png)

> If you use a different folder, update the relative paths accordingly.

## How PSO converges on Sphere (interpretation guide)
Each particle updates its velocity with **inertia**, **cognitive** (toward personal best $p_i$), and **social** (toward global best $g$) components. Positions then move by adding the new velocity.
You should see **best fitness** decrease rapidly at first as the swarm reaches the basin around the origin, then more slowly as it fine‑tunes.

**What to look for in your run output**
- A monotonic (or near‑monotonic) decline in the reported **best fitness**.
- Final **best position** close to the zero vector.
- Stable behavior (no explosions): if values saturate at bounds frequently, tweak bounds or inertia.

## Add your run results here
Paste key excerpts of your log (iterations and best fitness/position). Then summarize, for example:
> Early iterations: the swarm explores the search space within the bounds; $g$ changes frequently.  
> Mid iterations: $g$ stabilizes; most particles move into a tighter region.  
> Late iterations: small oscillations around the origin; best fitness $\approx 0$; best position near $\mathbf{0}$.

### Optional: convergence plot
If you export a per‑iteration `best_fitness` CSV, you can plot it with `scripts/plot_convergence.py`. A typical curve on Sphere is a smooth descending line that flattens near zero.
