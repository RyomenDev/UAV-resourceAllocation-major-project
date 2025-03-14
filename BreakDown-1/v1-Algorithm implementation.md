# Implementation of the Particle Swarm Optimization (PSO) algorithm for UAV resource allocation

C++ implementation of the Particle Swarm Optimization (PSO) algorithm for UAV resource allocation with inputs and a running example.

## Features of this Implementation

✅ **Takes input for:**

- n: Number of outposts
- m: Number of UAVs
- UAV details: Weight capacity, energy/km, total energy
- Outpost details: Resource needs (medicine, food, weapons), coordinates (x, y)
- Base station coordinates

✅ **Uses PSO to find the optimal UAV assignments** to minimize energy usage while ensuring high-priority deliveries.

## 📌 Example Input & Output

### 🔹Input:

```mathematica
Enter number of outposts: 3
Enter number of UAVs: 2
Enter UAV details (ID, weight capacity, energy/km, total energy):
1 50 2 100
2 60 1.5 120
Enter Outpost details (ID, medicine, food, weapons, x, y, priority):
1 20 10 5 5 10 3
2 15 20 10 10 5 4
3 10 15 5 8 8 2
Enter Base Station coordinates (x y): 0 0
```

### 🔹Output (Example):

```vbnet
Best UAV Allocation:
UAV 1 assigned to Outpost 1
UAV 2 assigned to Outpost 2
Best Energy Cost: 50.75
```

### 🔥 Summary

- **Optimized UAV assignments to minimize energy usage** while prioritizing deliveries.
- **Uses PSO** to improve the solution iteratively.
- **Flexible for real-world simulations** (supports different UAVs, outposts, and constraints).

### Future Reference

🚀 Add more constraints like UAV recharge stations / multi-stop deliveries
