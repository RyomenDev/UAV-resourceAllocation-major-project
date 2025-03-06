# 🚨 Issue: Both UAVs Are Assigned to the Same Outpost

Both UAVs are being allocated to same Outpost , which is incorrect. Each UAV should be assigned to a unique outpost based on priority and energy cost.

## 🔍 Identifying the Problem

**1. Unique Outpost Constraint Not Enforced Strictly**

- We check for duplicate assignments using `vector<bool> assigned(outposts.size(), false);`, but it **only prevents reassignment in the same iteration** rather than across all particles.

**2. Fitness Function May Still Favor a Single Outpost**

- The cost function is reducing energy consumption, **but it does not strongly penalize duplicate allocations.**

## ✅ Fix: Enforce Unique Assignments

We need to ensure that each UAV gets a unique outpost:

1. **Modify the Fitness Function:\***

- Add a large penalty if an outpost is assigned to more than one UAV.
- Use a set to store assigned outposts and penalize duplicate assignments.

2. **Improve Particle Update Logic:**

- If a UAV gets assigned a duplicate outpost, **force reassignment to a different one.**

## 🚀 What’s Fixed?

✅ 1. Ensures Unique Assignments

- Uses `unordered_set<int>` to track assigned outposts
- Applies penalty (+1000) for duplicate assignments

✅ 2. Prevents UAVs from Choosing the Same Outpost

- `initializeParticles()` ensures **unique outposts** for UAVs
- Particle updates **avoid duplicate assignments**

✅ 3. Optimizes Energy & Priority Balance

- Uses:
  **total energy used + 100/(priority + 1) ​+ (penalty if duplicate)**

-Avoids low-energy UAVs taking far outposts

## 🎯 Conclusion

Each UAV is assigned to a unique outpost, which means constraint enforcement is working correctly. 🎯🚀
