# UAV Resource Allocation System

## 📌 Overview

This project implements an optimized UAV (Unmanned Aerial Vehicle) allocation system for resource delivery to multiple outposts. It prioritizes UAV selection based on energy efficiency, capacity, distance, and urgency.

## 🚀 Features

- **Time-Based UAV Assignment**: Tracks UAV availability and assigns them efficiently.
- **Energy Optimization**: Ensures minimal energy usage per delivery.
- **Priority-Based Allocation**: Outposts with higher urgency are served first.
- **Failure Reporting**: Identifies unreachable outposts and provides reasons.

## 🛠️ Input Format

1. **UAV Details**:
   - `ID`, `Weight Capacity`, `Energy/km`, `Total Energy`
2. **Outpost Details**:
   - `ID`, `Medicine`, `Food`, `Weapons`, `Coordinates (x, y)`, `Priority (1-5)`
3. **Base Station Coordinates**:
   - `(x, y)`

### Example UAV Allocation

#### **Input:**

```
Enter number of outposts: 3
Enter number of UAVs: 2
Enter UAV details (ID, weight capacity, energy/km, total energy):
1 50 1.3 180
2 60 1.2 200
Enter Outpost details (ID, medicine, food, weapons, x, y, priority level 1-5):
1 20 10 5 5 10 3
2 15 20 10 10 5 4
3 10 10 5 20 30 5
Enter Base Station coordinates (x y): 0 0
```

#### **Processing Steps:**

1. **Calculate Distance for Each Outpost:**

   - Outpost 1: Distance = \(\sqrt{5^2 + 10^2} = 11.18\) km
   - Outpost 2: Distance = \(\sqrt{10^2 + 5^2} = 11.18\) km
   - Outpost 3: Distance = \(\sqrt{20^2 + 30^2} = 36.06\) km

2. **Energy Required to Reach Each Outpost and Return:**

   - UAV 1:

     - Outpost 1: \(2 \times 11.18 \times 1.3 = 29.07\) energy
     - Outpost 2: \(2 \times 11.18 \times 1.3 = 29.07\) energy
     - Outpost 3: \(2 \times 36.06 \times 1.3 = 93.75\) energy **(Exceeds UAV 1's total energy)**

   - UAV 2:
     - Outpost 1: \(2 \times 11.18 \times 1.2 = 26.83\) energy
     - Outpost 2: \(2 \times 11.18 \times 1.2 = 26.83\) energy
     - Outpost 3: \(2 \times 36.06 \times 1.2 = 86.54\) energy **(Exceeds UAV 2's total energy)**

3. **Assignment Strategy (Based on Priority & Availability):**
   - **UAV 2 assigned to Outpost 2 (Higher priority, feasible energy use).**
   - **UAV 1 assigned to Outpost 1 (Next highest priority, feasible energy use).**
   - **Outpost 3 is unreachable due to energy constraints.**

#### **Output:**

```
Best UAV Allocation:
UAV 2 assigned to Outpost 2
UAV 1 assigned to Outpost 1
Outpost 3 cannot be reached (Max reachable distance is 27.7 km)

Best Energy Cost: 2.39645
```

This ensures **optimal allocation** while handling **unreachable outposts** effectively. 🚀

# 🚀

It looks like both UAVs are getting assigned to Outpost 2, but Outpost 1 is being ignored, and Outpost 3 (which is far away) should be marked as unreachable. Let's debug this step by step:

### Potential Issues in the Code:

#### 1. Outpost Prioritization:

- Outpost 2 has a priority of **4**, which is higher than Outpost 1 (**3**).
- If UAVs are being assigned based on **priority alone**, Outpost 2 gets both UAVs, leaving Outpost 1 unassigned.

#### 2. UAV Energy Calculation:

- UAV 1: Energy **180**, Consumption **1.3/km** → Max Range = **180 / 1.3 ≈ 138 km** ✅
- UAV 2: Energy **200**, Consumption **1.2/km** → Max Range = **200 / 1.2 ≈ 166 km** ✅
- Outpost 3 is at **(20,30)** → Distance = **√(20² + 30²) = 36 km**, which is within range, so it **should be considered** instead of ignored.

#### 3. Sequential Assignment Issue:

- If the algorithm **first assigns both UAVs to Outpost 2**, then no UAVs remain for Outpost 1.
- The **expected output** should have UAVs **cover both Outpost 1 & 2** if energy allows, and Outpost 3 should be marked as **unreachable** if necessary.

### Fixing the Allocation Logic

- **Prioritize covering more outposts rather than assigning multiple UAVs to one**
- **Ensure energy constraints are checked properly**
- **Mark Outpost 3 as unreachable explicitly**

### Expected Output After Fixing:

```mathematica
Enter number of outposts: 3
Enter number of UAVs: 2
Enter UAV details (ID, weight capacity, energy/km, total energy):
1 50 1.3 180
2 60 1.2 200
Enter Outpost details (ID, medicine, food, weapons, x, y, priority level 1-5):
1 20 10 5 5 10 3
2 15 20 10 10 5 4
3 10 10 5 20 30 5
Enter Base Station coordinates (x y): 0 0

Best UAV Allocation:
UAV 1 assigned to Outpost 1
UAV 2 assigned to Outpost 2
Outpost 3 is **unreachable** (Max reachable distance is 36 km)

Best Energy Cost: X.XXXXX
```

### What to Do Next?

**🔹 Check your assignment logic** in the code to distribute UAVs to more outposts instead of both going to Outpost 2.
**🔹 Explicitly check energy constraints** for all outposts.
**🔹 Ensure unreachable outposts are reported properly**

# 🚀
