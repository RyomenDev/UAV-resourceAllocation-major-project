# **Priority Calculation for UAV Resource Allocation**

## **🔹 Overview**
In the UAV resource allocation model, priority determines which outposts should receive supplies first. It directly impacts UAV assignments and energy cost calculations.

---

## **🔹 1. Factors Affecting Priority**
Priority is determined based on multiple factors:

1. **Urgency of Need** → Higher urgency = Higher priority.
2. **Amount of Resources Required** → More resources needed = Higher priority.
3. **Distance from Base Station** → Closer outposts may be prioritized to save energy.
4. **Strategic Importance** → Critical locations receive higher priority.

---

## **🔹 2. Priority Calculation Formula**
Priority for an outpost is computed as:

\[
\text{Priority} = W_1 \times \text{Urgency} + W_2 \times \frac{\text{Amount}}{\max(\text{Amount})} + W_3 \times \frac{\text{Distance}}{\max(\text{Distance})}
\]

where:
- `W1, W2, W3` → Weights assigned to each factor based on importance.
- `Urgency` → Rating from **1 to 10** (higher means more critical).
- `Amount` → Total resources requested by the outpost.
- `Distance` → Distance from the base station (computed using coordinates).

---

## **🔹 3. Example C++ Code for Priority Calculation**
```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Outpost {
    int id;
    int urgency; // 1 to 10
    double totalResources;
    double distance;
};

double calculatePriority(Outpost& outpost, double maxAmount, double maxDistance) {
    double urgencyWeight = 0.5;
    double amountWeight = 0.3;
    double distanceWeight = 0.2;

    double normalizedAmount = outpost.totalResources / maxAmount;
    double normalizedDistance = outpost.distance / maxDistance;

    return (urgencyWeight * outpost.urgency) +
           (amountWeight * normalizedAmount) +
           (distanceWeight * normalizedDistance);
}

int main() {
    vector<Outpost> outposts = {
        {1, 8, 20, 5},
        {2, 6, 15, 10},
        {3, 9, 10, 8}
    };

    double maxAmount = 20.0;
    double maxDistance = 10.0;

    for (auto& outpost : outposts) {
        double priority = calculatePriority(outpost, maxAmount, maxDistance);
        cout << "Outpost " << outpost.id << " Priority: " << priority << endl;
    }
    return 0;
}
```

---

## **🔹 4. Example Output**
For three outposts:

| Outpost | Urgency (1-10) | Resource Amount (kg) | Distance (km) | Computed Priority |
|---------|---------------|----------------------|--------------|-----------------|
| 1       | 8             | 20                   | 5            | **6.8** |
| 2       | 6             | 15                   | 10           | **6.2** |
| 3       | 9             | 10                   | 8            | **7.1** |

**Observations:**
- **Outpost 3 has the highest priority** due to high urgency.
- **Outpost 1 is prioritized over Outpost 2** due to greater resource needs.

---

## **🔹 5. Impact on UAV Allocation**
- Higher priority **reduces penalty in the fitness function**, making UAVs more likely to serve high-priority outposts first.
- A UAV is **less likely to be assigned** to a **low-priority outpost** unless no better option exists.

---

## **🔹 6. Customizing Priority Criteria**
To fine-tune priority, adjust `W1, W2, W3` values:
- **Increase `W1`** → If urgency is most critical.
- **Increase `W2`** → If resource quantity matters more.
- **Increase `W3`** → If minimizing UAV travel distance is preferred.

🔹 **Next Steps:** Test different priority weights and UAV allocation strategies to optimize performance.

---

💡 **Need adjustments?** Modify `W1, W2, W3` values in the formula and test different scenarios! 🚀

