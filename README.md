---

## Visual intuition

<p align="center">
  <img src="docs/pso_periodic_contours.png" alt="PSO on a periodic, multimodal landscape (contour plot with swarm path)" width="640">
</p>

**Figure 1 — PSO on a periodic, multimodal surface.**  
The rippled contours represent a landscape with many local minima (periodic “basins”).  
Orange markers trace successive particle positions: the swarm samples multiple basins, then drifts toward a deeper valley as information diffuses via the global best. This is the classic PSO behavior on hard, bumpy terrains.

---

<p align="center">
  <img src="docs/sphere_bowl_and_contours.png" alt="Sphere function: 3D bowl and 2D contour with global minimum at the origin" width="960">
</p>

**Figure 2 — Sphere benchmark (what this repo runs by default).**  
Left: the smooth quadratic “bowl” with global minimum at **x = 0**.  
Right: 2D contours centered at the origin. On this convex objective PSO contracts cleanly toward the center; it’s a good sanity check for settings like inertia `w`, cognitive/social gains `c1`, `c2`, and velocity/position clamps.

---

<p align="center">
  <img src="docs/pso_multimodal_path.png" alt="PSO trajectory across a multimodal surface with several peaks/valleys" width="960">
</p>

**Figure 3 — Crossing basins on a multimodal surface.**  
Red points show the best-so-far positions over time. You can see PSO “jumping” across ridges and settling into a deeper basin as particles share information. This is why PSO is often preferred when gradients are unavailable, noisy, or misleading.

> ℹ️ If your file names differ, replace the three `docs/*.png` paths above with your own:
> - `docs/pso_periodic_contours.png` → your periodic/rippled contour image  
> - `docs/sphere_bowl_and_contours.png` → your sphere bowl + contour image  
> - `docs/pso_multimodal_path.png` → your multimodal surface path image

---

## Real-world applications of PSO in intelligent systems & robotics

PSO is handy whenever you can **score** a candidate solution but don’t have (or don’t trust) gradients.

- **Controller tuning (PID / MPC gains):** minimize tracking error + control effort; works directly on hardware-in-the-loop or Gazebo/ROS sim.
- **Trajectory & path optimization:** fit splines/corridors to reduce length, jerk, and collision penalties; useful for mobile robots and manipulators.
- **Sensor & camera calibration:** optimize intrinsics/extrinsics by minimizing reprojection or map-consistency error.
- **Multi-robot task allocation & formation control:** assign tasks/waypoints or formation parameters to minimize mission time and energy.
- **Localization/SLAM parameter search:** tune filter/process-noise and loop-closure thresholds to improve robustness on real datasets.
- **Coverage & exploration planning (UAV/UGV):** pick viewpoints/paths that maximize mapped area or information gain under budget constraints.
- **Scheduling & resource optimization:** balance battery, charging, and mission windows in fleets.
- **ML for robotics:** quick hyperparameter searches for perception models (e.g., thresholds, augment mixes, lightweight nets) when full HPO is overkill.

> TL;DR: If you can write a **fitness function**, PSO will search that space—no gradients required, tolerant to noise, and simple to implement/parallelize.
