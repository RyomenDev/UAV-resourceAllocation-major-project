# Randomness in Result - PSO

The reason for getting **different results for the same input** is because of the **randomness** in Particle Swarm Optimization (PSO). PSO uses **random initialization** for the UAV assignments and velocities, leading to variations in results across multiple runs.

The issue with `Best Energy Cost: 1.79769e+308` (which is `numeric_limits<double>::max()`) happens when a solution is invalid (e.g., UAVs running out of energy). This means the algorithm failed to find a feasible solution, leading to an extremely high cost.

### 🔹 Fixes & Improvements

**1. Make results consistent**

- Use `srand(0);` at the start of `main()` to fix randomness.

**2. Ensure valid UAV assignments**

- **Reject unfeasible assignments** (if a UAV cannot reach an outpost due to energy limits).

**3. Improve Velocity Updates**

- Ensure assignments stay within valid ranges `(0 to n-1)`.

### 🔹 Key Fixes

✅ Fixed Randomness

- Used `srand(0);` to ensure consistent results on every run.

✅ Fixed Infinite Energy Cost Issue

- **Rejects invalid UAV assignments** if they **cannot reach an outpost due to energy** limits.

✅ Better Velocity Updates

- Ensures UAVs stay **within valid outpost ranges** `(0 to n-1)`.

✅ Handles Zero Energy Cases

- Returns `numeric_limits<double>::max()` only when absolutely necessary.

## 🎯 Summary

- The Issue was caused by randomness + invalid assignments
- Now results will be consistent & realistic
- Further improvements possible (multi-objective optimization, UAV recharging, etc.)
