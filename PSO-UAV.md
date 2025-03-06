# Particle Swarm Optimization (PSO)

For **UAV Resource Allocation** problem, **Particle Swarm Optimization (PSO)** is the best swarm algorithm. Here’s why:

## Why PSO?

✅ **Continuous Optimization:** Unlike Ant Colony Optimization (ACO), which is more suited for discrete pathfinding, PSO works well for continuous resource allocation.
✅ **Efficient Convergence:** PSO quickly finds optimal UAV assignments with minimal computational overhead.
✅ **Adaptive Learning:** UAVs adjust their allocation dynamically based on energy, distance, and priority constraints.

## Simulation Model using PSO

We'll use **PSO** to optimize **UAV assignments to outposts** while minimizing **energy consumption and prioritizing urgent deliveries.**

### 1. Problem Representation in PSO

- **Particles (Solutions):** Each particle represents a possible assignment of UAVs to outposts.
- **Position:** A matrix where X[i][j] represents UAV i assigned to Outpost j.
- **Velocity:** Defines how UAV assignments change in the next iteration.
- **Fitness Function:** Evaluates how good a solution is based on:
  - **Energy Consumption:** Ensure UAVs do not exceed their available energy.
  - **Delivery Efficiency:** Prioritize high-urgency outposts first.
  - **Minimized Travel Distance:** Assign UAVs to closer outposts when possible.

### 2. Steps for PSO Simulation

**Step 1: Initialize UAVs and Outposts**

- Each UAV has weight capacity, energy/km, total energy available.
- Each outpost has demands for medicine, food, and weapons with priority levels.

**Step 2: Generate Initial Population of Solutions**

- Randomly assign UAVs to outposts based on constraints.

**Step 3: Evaluate Fitness Function**

- Calculate total energy consumption & ensure no UAV exceeds its energy capacity.
- Prioritize deliveries based on urgency.
- Minimize overall travel distance.

**Step 4: Update Particles**

- Adjust assignments using PSO velocity and position updates.
- Best solutions are carried forward to the next iteration.

**Step 5: Repeat Until Convergence**

- Stop when an optimal assignment is found that minimizes energy usage while maximizing resource delivery efficiency.
