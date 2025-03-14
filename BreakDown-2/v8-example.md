## 🚀 Updated Strategy
1. Priority Queue (Min-Heap) for UAV Scheduling
- UAVs are assigned based on **earliest available time**, ensuring **parallel execution**.
2. Track Time Taken for Each UAV
- Start Time → Travel Time → Return Time → Available Again.
3. Optimize for Fastest Allocation with Minimal Fuel
- Consider both **distance** and **time efficiency**.
4. Failure Handling
- If no UAV can reach an outpost, print a **failure reason**.

## 📌 Example Run

### 📝 Input

```
Enter number of outposts: 5
Enter number of UAVs: 2
Enter UAV details (ID, weight capacity, energy/km, total energy):
1 50 1.2 180
2 60 1.1 250
Enter Base Station coordinates (x y): 0 0
Enter Outpost details (ID, medicine, food, weapons, x, y, priority level 1-5):
1 20 10 5 5 5 3
2 15 20 10 12 8 5
3 10 10 5 20 25 4
4 15 20 10 12 8 2
5 20 10 5 5 5 2

```

✅ Expected Output
```
Best UAV Allocation:
UAV 1 assigned to Outpost 2 | Distance: 14.4222 | Energy Cost: 34.6133 | Travel Time: 1.44222 | Available Again At: 2.88444
UAV 2 assigned to Outpost 3 | Distance: 32.0156 | Energy Cost: 70.4344 | Travel Time: 3.20156 | Available Again At: 6.40312
UAV 1 assigned to Outpost 1 | Distance: 7.07107 | Energy Cost: 16.9706 | Travel Time: 0.707107 | Available Again At: 4.29865        
UAV 1 assigned to Outpost 4 | Distance: 14.4222 | Energy Cost: 34.6133 | Travel Time: 1.44222 | Available Again At: 7.1831
UAV 2 assigned to Outpost 5 | Distance: 7.07107 | Energy Cost: 15.5563 | Travel Time: 0.707107 | Available Again At: 7.81734 

```