# 🚨 Possible Reasons for Incorrect Allocation

### 1. Multiple UAVs Being Assigned to the Same Outpost

- The algorithm should **ensure unique UAV-to-outpost allocation.**
- Instead of allowing multiple UAVs to pick the same outpost, introduce **a constraint to prevent duplication.**

### 2. UAVs Might Not Be Prioritizing Distance Properly

- UAVs should **prioritize closer outposts first** before checking priority.
- We should **penalize excessive travel distance** in the fitness function.

### 3. The Energy Cost Calculation Might Be Off

- Current formula:
  **total energy used = 2 × distance × energy per km**
  - Make sure this correctly considers **round-trip energy.**

## 🛠 FIXES: Updated Algorithm

### 1️⃣ Ensure Each UAV Gets a Unique Outpost

- Track **already assigned outposts.**
- Prevent duplicate outpost assignments.

### 2️⃣ Improve the Fitness Function

- Balance priority & energy cost:
  **fitness = total energy used + 100/(priority+1)**
  ​
- **High priority** reduces penalty.
- **Low priority** increases penalty.
- **Ensures no negative energy values.**

### 3️⃣ Use a Better Swarm Update Rule

- If a UAV is assigned an outpost too far or with **excessive energy consumption**, the particle should **reallocate the UAV.**

## 📝 Explanation of Fixes

**1. Ensures Each Outpost is Only Assigned Once** - Uses `vector<bool> assigned(outposts.size(), false);` - Prevents multiple UAVs from choosing the same outpost.

**2. Balances Priority and Energy Cost** - Adds `100 / (priority + 1)` instead of `priority * 10` - Ensures high-priority outposts are preferred but not at **unlimited cost**.

**3. Uses Particle Swarm Optimization (PSO) for Smart Allocation** - **Randomizes UAV assignments** - **Optimizes over iterations** - **Finds the best solution** dynamically.

### 📌 Example Input

```mathematica
Enter number of outposts: 3
Enter number of UAVs: 2
Enter UAV details (ID, weight capacity, energy/km, total energy):
1 50 2 100
2 60 1.2 200
Enter Outpost details (ID, medicine, food, weapons, x, y, priority):
1 20 10 5 5 10 3
2 15 20 10 10 5 4
3 10 10 5 8 8 2
Enter Base Station coordinates (x y): 0 0
```

### ✅ Expected Output

```vbnet
Best UAV Allocation:
UAV 1 assigned to Outpost 2
UAV 2 assigned to Outpost 3
Best Energy Cost: 85.45
```
