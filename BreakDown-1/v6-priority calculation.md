# Priority calculation

UAV resource allocation using **Particle Swarm Optimization (PSO)** while incorporating **priority calculation** in the decision-making process. The priority is calculated based on resource urgency, **distance from the base station, and the outpost's criticality level**.

## Priority Calculation Formula
The priority of an outpost is determined using:

**Priority Score= α × Resource Urgency + β × (1 / Distance) + γ × Criticality Level**

where:

- **Resource Urgency:** Total required resources (medicine + food + weapons).
- **Distance:** Euclidean distance from the base station.
- **Criticality Level:** A manually assigned value based on the outpost's importance (higher means more critical).
- **α, β, γ:** Weight factors to balance importance.

### How This Works

- **Priority Calculation:** Uses urgency, distance, and criticality.
- **PSO Algorithm:** Optimizes the UAV assignments to minimize energy cost.
- **Fitness Function:** Evaluates each UAV’s energy efficiency based on priority-weighted cost.

This ensures UAVs prioritize high-importance outposts while minimizing total energy cost.

# 🚀