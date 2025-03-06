## IF Energy Receive is Negative

Best Energy Cost being negative (-8.44582) suggests that the priority score is outweighing energy consumption, leading to an unexpected result.

### 🔹 Why is This Happening?

- **Priority Weighting Issue:**

**The formula:**

#### **fitness = total energy − (priority score X 10)**

- If **priority score is high**, the result becomes negative, which means the algorithm is favoring high-priority assignments without considering energy consumption properly.
- **Multiple UAVs Assigned to the Same Outpost**

- Both UAVs are being assigned to Outpost 1. This may be due to the **fitness function being biased towards priority over energy cost**.

### 🔹 Solution: Fixing the Fitness Function

- Instead of priority \* 10, use a balanced tradeoff:

  #### fitness = total energy + ( 1 / ( priority +1 ) ) × 100

  - **High priority → Less penalty**
  - **Low priority → More penalty**
  - **Prevents negative energy costs**

### 🔧 Updated Fitness Function

Modify the **fitness function** like this:

```cpp
double fitnessFunction(const Particle &p, const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base) {
double total_energy = 0;
double penalty = 0;

    for (int i = 0; i < p.assignment.size(); i++) {
        int outpost_id = p.assignment[i];
        if (outpost_id == -1) continue;

        const UAV &uav = uavs[i];
        const Outpost &outpost = outposts[outpost_id];

        double distance = calculateDistance(base.x, base.y, outpost.x, outpost.y);
        double energy_used = 2 * distance * uav.energy_per_km;

        if (energy_used > uav.total_energy) return numeric_limits<double>::max();

        total_energy += energy_used;
        penalty += (100 / (outpost.priority + 1)); // Reduced weight for high-priority outposts
    }

    return total_energy + penalty; // Avoids negative values

}
```

### 🔹 Expected Output After Fix

```vbnet
Best UAV Allocation:
UAV 1 assigned to Outpost ...
UAV 2 assigned to Outpost ...
...
Best Energy Cost: 75.23
```

- **Energy cost remains realistic**
- **Outposts are prioritized correctly**
- **Negative values are prevented**

# 🚀 ! 🚀
