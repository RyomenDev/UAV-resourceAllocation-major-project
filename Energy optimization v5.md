## 🔍 Potential Issues & Further Improvements

### 1. Energy Cost Seems High (116.554)

- This suggests that UAVs might not be assigned to the **closest or most efficient outposts**.
- We should check if there are better assignments with **lower energy consumption**.

### 2. Distance Factor Might Not Be Optimized

- The energy cost is largely influenced by **distance** and **UAV efficiency (energy/km)**.
- We can **further fine-tune the fitness function** to ensure UAVs choose **outposts with minimum travel cost**.

### 3. Check for Swapping Possibilities

- If **UAV 1 is assigned to Outpost 2** and **UAV 2 is assigned to Outpost 1**, we should check:
- What happens if we swap the assignments?
  Does this lead to a **lower energy cost?**

## ✅ Next Steps

### 1. Debugging the Energy Calculation

- Print individual UAV energy usage to see where the **highest cost comes from**.
- Ensure UAVs with **higher energy efficiency (lower energy/km)** are assigned to **farther outposts**.

### 2. Implement a Swap Check

- After PSO finds a solution, check if swapping UAVs **reduces total energy**.
- If swapping improves efficiency, update the solution.

### 3. Fine-Tune the Fitness Function

- Currently, priority adds `100/(priority + 1`) to energy cost.

  - Alternative: Use a weighted formula that prioritizes energy savings.
  - Example:

  ```cpp
  total_energy += energy_used \* (1 + (5 / (outpost.priority + 1)));
  ```

  - This **penalizes low-priority outposts** more while favoring low energy cost.

## 📌 Plan of Action

**1. Print UAV-wise energy usage**.
**2. Add a post-PSO optimization swap**.
**3. Refine the energy calculation for better balancing**.

# 🚀
