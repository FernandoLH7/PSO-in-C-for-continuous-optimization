## Visual intuition

<p align="center">
  <img src="docs/ParticleSwarmArrowsAnimation.gif" alt="PSO on a rippled, periodic landscape: particles exploring and drifting toward a deeper basin" width="640">
</p>

**Figure 1 — PSO on a periodic, multimodal surface (exploration → drift).**  
The wavy contour lines represent many local minima. Arrows/paths show velocity-driven motion; orange markers are particle positions per frame. Early on, particles scatter and sample several basins (inertia `w` dominates). As the global best improves, the **social pull** `c2 r2 [g - x]` starts to “align” velocities and the cloud **drifts** toward the best basin found so far.  
**What to look for:**  
- Wide wandering at the start = higher `w` / higher `V_MAX` → better exploration.  
- Gradual coherent motion = social term taking over as a good basin is discovered.  
- If you see particles ping-pong across ridges, lower `V_MAX` or slightly reduce `c1,c2`.

---

<p align="center">
  <img src="docs/pso_convex.gif" alt="Sphere function: 3D quadratic bowl and 2D contour map with the global minimum at the origin" width="960">
</p>

**Figure 2 — Sphere benchmark (controlled contraction).**  
Left: a convex quadratic bowl; right: concentric contours with the minimum at the origin. On this landscape, PSO behaves like a **contractive flow**—velocities shrink and positions spiral inward. You can “read” parameter effects directly:  
- Larger `w` → wider spirals (slower settle).  
- Larger `c1` (cognitive) → particles hover near their personal bests longer (more local probing).  
- Larger `c2` (social) → a stronger pull to the center once a good global best is discovered.  
This animation is ideal for sanity-checking clamps and a **decay schedule** for `w` (e.g., 0.9 → 0.4).

---

<p align="center">
  <img src="docs/pso_nonconvex.gif" alt="PSO traversing a multimodal surface with several peaks/valleys; red points track the current best-so-far" width="960">
</p>

**Figure 3 — Basin hopping on a rugged surface.**  
Red dots track the **best-so-far** solution. Notice the swarm occasionally **jumps basins**: a single particle stumbles into a better valley, updates the global best, and the group re-orients. This is PSO’s strength when gradients are unavailable or misleading.  
**Reading failure modes in the animation:**  
- **Stuck early** (everyone circling one mediocre basin): raise `P` or `V_MAX`, or start with a higher `w`.  
- **Chaotic overshoot** near good basins: reduce `V_MAX` or `c1,c2`, or add damping by decaying `w` faster.

---

## How PSO behaves (and how that shows up in the visuals)

- **Inertia `w`** keeps momentum → broad exploration (wide early arcs in Fig. 1–3).  
- **Cognitive pull `c1`** → particles revisit their own good spots (tight loops around personal bests).  
- **Social pull `c2`** → coherent motion toward the global best (the whole cloud “leans” the same way).  
- **Velocity clamp `V_MAX`** → controls step size; too high = ping-pong, too low = crawl.  
- **Position clamp** → keeps candidates feasible; reflection at bounds avoids corner pile-ups.

**Cheat settings that work well**
- Start explorative, finish exploitative: decay `w` linearly from ~`0.9 → 0.4`.  
- Keep `c1 ≈ c2` in `[1.5, 2.0]`.  
- Set `V_MAX` ≈ `0.1–0.2 × (X_MAX − X_MIN)` per dimension.

**Optional (constriction form)**  
Instead of inertia, you can use the Clerc–Kennedy constriction factor:
$\[
\chi = \frac{2}{\phi - 2 + \sqrt{\phi^2 - 4\phi}},\quad \phi=c_1+c_2>4
\]$
A common pick is $\(c_1=c_2=2.05\)$ giving $\(\chi\approx0.729\)$. Both forms are valid; inertia is simpler to tune.

---

## Reading the console log (quick diagnostics)

- **Healthy**: steep early drop, then a smooth descent or tiny wiggles near the end (Fig. 2 style).  
- **Flat from the start**: increase `P` or `V_MAX`, or widen search bounds.  
- **Oscillations**: decrease `V_MAX`, or slightly reduce `c1,c2`, or decay `w` faster.  
- **Late plateau**: let it run longer, or push a lower terminal `w`, or add a soft restart for a few worst particles.
