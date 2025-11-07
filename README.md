## Visual intuition

<p align="center">
  <img src="docs/ParticleSwarmArrowsAnimation.gif" alt="PSO on a rippled, periodic landscape: particles exploring and drifting toward a deeper basin" width="640">
</p>

**Figure 1 — PSO on a periodic, multimodal surface.**  
The wavy contour lines indicate many local minima. The orange “x” markers show successive particle locations. The swarm samples multiple basins early, then information sharing (global best) pulls it toward a deeper valley.

<p align="center">
  <img src="docs/Captura%20de%20pantalla%202025-11-07%20131704.png" alt="Sphere function: 3D quadratic bowl and 2D contour map with the global minimum at the origin" width="960">
</p>

**Figure 2 — Sphere benchmark (this repo’s default).**  
Left: the quadratic bowl; right: concentric contours centered at the origin. On this convex objective, PSO contracts cleanly to **x = 0**. It’s a sanity check for `w`, `c1`, `c2`, and clamping settings.

---

<p align="center">
  <img src="docs/Captura%20de%20pantalla%202025-11-07%20131716.png" alt="PSO traversing a multimodal surface with several peaks/valleys; red points track the current best-so-far" width="960">
</p>

**Figure 3 — Crossing basins on a multimodal surface.**  
Red points track the best-so-far solution over time. You can see “hops” across ridges as particles share information, eventually settling in a deeper basin. This illustrates why PSO is useful when gradients are unavailable, noisy, or misleading.

> Tip: Filenames with spaces are URL-encoded above. If you prefer cleaner paths, rename them (e.g., `pso_periodic_contours.png`, `sphere_bowl_contours.png`, `pso_multimodal_path.png`) and update the `src`.

---

## Real-world applications in intelligent systems & robotics

PSO shines whenever you can **score** a candidate but don’t have (or don’t trust) gradients.

- **Controller tuning (PID/MPC):** minimize tracking error + control effort (HIL or Gazebo/ROS).
- **Trajectory & path optimization:** fit splines/corridors to reduce length, jerk, and collision penalties (UGV/UAV/manipulators).
- **Sensor/camera calibration:** optimize intrinsics/extrinsics via reprojection or map-consistency error.
- **Multi-robot task allocation & formation:** assign tasks/waypoints or formation parameters to minimize time and energy.
- **SLAM/Localization parameter search:** tune noise models and loop-closure thresholds for robustness.
- **Coverage & exploration planning:** choose viewpoints/paths maximizing mapped area or information gain under budget constraints.
- **Scheduling & fleet ops:** balance battery, charging, and mission windows.
- **ML in robotics:** quick hyperparameter sweeps for perception modules when full HPO is overkill.

> TL;DR: If you can write a **fitness function**, PSO will search that space—gradient-free, noise-tolerant, and simple to parallelize.
