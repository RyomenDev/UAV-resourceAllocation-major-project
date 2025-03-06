
# UAV Resource Allocation using Particle Swarm Optimization (PSO)

## Overview
This project implements the **Particle Swarm Optimization (PSO)** algorithm for **UAV (Unmanned Aerial Vehicle) resource allocation**. The goal is to efficiently allocate UAVs to deliver essential resources such as **medicine, food, and weapons** to outposts while minimizing energy consumption and ensuring high-priority deliveries.

## Features
✅ **Takes input for:**
- **n**: Number of outposts
- **m**: Number of UAVs
- **UAV details**: Weight capacity, energy/km, total energy
- **Outpost details**: Resource needs (medicine, food, weapons), coordinates (x, y)
- **Base station coordinates**

✅ **Uses PSO to optimize assignments:**
- Minimizes energy consumption
- Prioritizes urgent resource deliveries
- Allocates UAVs based on travel distance and energy constraints

## How it Works
1. **Input Processing**: Reads the number of UAVs, outposts, and their respective details.
2. **Initialization**: Generates an initial swarm of potential UAV allocation solutions.
3. **Particle Movement**: Iteratively updates solutions based on velocity, local best, and global best solutions.
4. **Fitness Evaluation**: Computes energy consumption and ensures UAVs meet resource constraints.
5. **Convergence**: Continues optimization until an optimal or near-optimal allocation is found.

## Installation & Usage
### **Prerequisites**
- C++ Compiler (GCC, Clang, or MSVC)
- C++ Standard Library

### **Compilation & Execution**
```bash
 g++ -o uav_allocation main.cpp -std=c++17
 ./uav_allocation
```

<!-- ### **Input Format**
```
Number of Outposts: 3
Number of UAVs: 2
Base Station: (0,0)
UAV 1: Weight Capacity = 10, Energy/km = 2, Total Energy = 100
UAV 2: Weight Capacity = 15, Energy/km = 3, Total Energy = 120
Outpost 1: Medicine = 5, Food = 3, Weapons = 2, Location (x, y) = (5, 5)
Outpost 2: Medicine = 4, Food = 6, Weapons = 1, Location (x, y) = (10, 10)
```

### **Output Example**
```
Optimal UAV Assignments:
UAV 1 -> Outpost 1 (Energy Used: 20)
UAV 2 -> Outpost 2 (Energy Used: 30)
Total Energy Consumption: 50
``` -->

## Applications
🚀 **Disaster Response** – Optimally deploy UAVs to deliver medical aid and supplies
🚀 **Military Operations** – Efficiently allocate UAVs for supply distribution in remote areas
🚀 **Logistics & Supply Chain** – Automating resource delivery using UAV fleets

## Future Possible Improvements
🔹 Incorporate **multi-objective optimization** (e.g., delivery time, fuel efficiency)
🔹 Implement **hybrid metaheuristic algorithms** (e.g., Genetic Algorithm + PSO)
🔹 Extend to **real-time dynamic allocation** with changing outpost demands
🔹 UAV **recharge stations** 
🔹 **multi-stop deliveries**

## License
This project is open-source under the **MIT License**.

## Contributors
- **Akash Mishra** (Developer & Researcher)
- **Biranjay Kumar Gupta** (Developer & Researcher)
- **Sunny Kumar** (Developer & Researcher)

For queries, reach out via GitHub or email.

---
🚀 **Optimizing UAV resource allocation using AI-driven heuristics!** 🚀

