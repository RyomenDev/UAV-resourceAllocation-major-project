## 🔹 1. Fitness Function: Evaluating the Solution

### Purpose:

The **fitness function** is used to **evaluate how good a solution (UAV allocation)** is based on:

**1. Total Energy Cost**

- Energy consumed by UAVs while traveling from the base station to the outpost and back.

**2. Priority Consideration**

- Outposts with higher priority should be served efficiently.

**3. Weight Capacity Constraint**

- The UAV must be able to carry all the required resources.

#### Typical Fitness Calculation Formula:

```cpp
double fitnessFunction(vector<int>& allocation, vector<UAV>& uavs, vector<Outpost>& outposts, BaseStation& base) {
    double totalEnergy = 0;

    for (int i = 0; i < allocation.size(); i++) {  // Loop through each UAV
        int assignedOutpost = allocation[i];

        if (assignedOutpost != -1) {  // Check if UAV is assigned to an outpost
            UAV& uav = uavs[i];
            Outpost& outpost = outposts[assignedOutpost];

            // Calculate distance between UAV and outpost
            double distance = calculateDistance(base, outpost);
            double roundTripDistance = 2 * distance; // UAV has to return to base

            // Calculate energy required for the trip
            double energyUsed = roundTripDistance * uav.energyPerKm;

            // Apply priority penalty (higher priority -> lower penalty)
            double priorityPenalty = 100 / (outpost.priority + 1);

            totalEnergy += (energyUsed + priorityPenalty);
        }
    }
    return totalEnergy;
}
```

#### Breakdown:

1.  **Loop through all UAVs** and check which outpost they are assigned to.
2.  **Calculate the round-trip distance** from the **base station → outpost → base station**.
3.  **Compute energy usage** as:

            energy=distance×UAV energy/km

4.  **Add a priority penalty** so that UAVs prioritize higher-priority outposts.

## 🔹 2. initializeParticles(): Creating Initial Population

### Purpose:

This function initializes the **swarm of particles**, each representing a **possible UAV allocation solution**.

### How It Works:

- Each particle represents a **random assignment of UAVs to outposts**.
- The velocity for each UAV is also randomly initialized.

### Code Snippet:

```cpp
void initializeParticles(vector<Particle>& swarm, int numUAVs, int numOutposts) {
    for (auto& particle : swarm) {
        // Randomly assign UAVs to outposts
        for (int i = 0; i < numUAVs; i++) {
            particle.position[i] = rand() % numOutposts;  // Assign to a random outpost
            particle.velocity[i] = (rand() % numOutposts) - (numOutposts / 2); // Random velocity
        }

        // Set initial best known positions
        particle.bestPosition = particle.position;
        particle.bestFitness = DBL_MAX;
    }
}
```

### Breakdown:

1. **Each particle (solution) is initialized randomly:**
   - Each UAV is randomly assigned to an **outpost ID**.
   - Each UAV’s movement velocity is set to a **random number**.
2. **Best known position** for each particle is set to the initial position.
3. **Fitness value is set to a very high number (DBL_MAX)**, meaning we haven't found a good solution yet.

## 🔹 3. pso(): Running the Particle Swarm Optimization

### Purpose:

This function **optimizes the UAV allocation** using the PSO algorithm.

### Key Steps:

1. **Initialize a swarm** of solutions.
2. **Evaluate each solution** using the fitness function.
3. **Update particle velocities and positions** based on the best-known solutions.
4. **Repeat until convergence** (i.e., when the best solution stops improving).

## Code Snippet:

```cpp
void pso(vector<UAV>& uavs, vector<Outpost>& outposts, BaseStation& base) {
    vector<Particle> swarm(NUM_PARTICLES);
    initializeParticles(swarm, uavs.size(), outposts.size());

    vector<int> globalBestPosition;
    double globalBestFitness = DBL_MAX;

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        for (auto& particle : swarm) {
            // Evaluate fitness
            double fitness = fitnessFunction(particle.position, uavs, outposts, base);

            // Update personal best
            if (fitness < particle.bestFitness) {
                particle.bestFitness = fitness;
                particle.bestPosition = particle.position;
            }

            // Update global best
            if (fitness < globalBestFitness) {
                globalBestFitness = fitness;
                globalBestPosition = particle.position;
            }
        }

        // Update velocity and position for each particle
        for (auto& particle : swarm) {
            for (int i = 0; i < particle.position.size(); i++) {
                double inertia = W * particle.velocity[i]; // Inertia weight
                double cognitive = C1 * (rand() / double(RAND_MAX)) * (particle.bestPosition[i] - particle.position[i]);
                double social = C2 * (rand() / double(RAND_MAX)) * (globalBestPosition[i] - particle.position[i]);

                // Update velocity
                particle.velocity[i] = inertia + cognitive + social;

                // Update position
                particle.position[i] += particle.velocity[i];

                // Ensure position is within valid bounds (0 to numOutposts - 1)
                if (particle.position[i] < 0) particle.position[i] = 0;
                if (particle.position[i] >= outposts.size()) particle.position[i] = outposts.size() - 1;
            }
        }
    }

    // Print best solution
    cout << "Best UAV Allocation:\n";
    for (int i = 0; i < globalBestPosition.size(); i++) {
        cout << "UAV " << i + 1 << " assigned to Outpost " << globalBestPosition[i] + 1 << endl;
    }
    cout << "Best Energy Cost: " << globalBestFitness << endl;
}
```

## Breakdown of PSO Steps

1. **Initialize the swarm** using `initializeParticles()`.
2. Loop for `MAX_ITERATIONS`:
    - Compute fitness of each particle.
    - Update **personal best** (each particle's best solution).
    - Update **global best** (best solution among all particles).
3. **Update each particle’s velocity and position** using the PSO update equation:

![Image](https://github.com/user-attachments/assets/ab90f5eb-22b8-405a-a67e-8b74b7fb649e)

            w = inertia weight (balances exploration and exploitation)
            c1, c2 = learning factors (control influence of personal & global best)
            r1, r2 = random numbers (adds randomness)

4. **Ensure UAVs remain assigned to valid outposts** (position clamping).
5. **After all iterations, print the best allocation found**.

🔹 Summary
![Image](https://github.com/user-attachments/assets/d0eb0a2d-138a-44ad-a129-dfaf14cb8e2a)

# 🚀 Next Steps
- **Debug why the energy cost is fluctuating**.
- **Try different inertia (W), cognitive (C1), and social (C2) parameters** for better convergence.
- **Check if the best assignment is truly optimal** by manually comparing energy usage.