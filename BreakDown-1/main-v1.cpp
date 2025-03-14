#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// UAV structure
struct UAV {
    int id;
    double weight_capacity;
    double energy_per_km;
    double total_energy;
};

// Outpost structure
struct Outpost {
    int id;
    int medicine, food, weapons; // Resources needed
    double x, y; // Coordinates
    int priority; // Priority level (1-5)
};

// Base station coordinates
struct BaseStation {
    double x, y;
};

// Distance calculation function
double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Particle structure for PSO
struct Particle {
    vector<int> assignment; // UAV assignments to outposts
    vector<double> velocity;
    double fitness;
};

// PSO Constants
const int NUM_PARTICLES = 10;
const int MAX_ITERATIONS = 50;
const double W = 0.5;  // Inertia
const double C1 = 1.5; // Cognitive component
const double C2 = 1.5; // Social component

// Fitness function: Minimize energy while considering priority
double fitnessFunction(const Particle &p, const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base) {
    double total_energy = 0;
    double priority_score = 0;

    for (int i = 0; i < p.assignment.size(); i++) {
        int outpost_id = p.assignment[i];
        if (outpost_id == -1) continue; // No assignment

        const UAV &uav = uavs[i];
        const Outpost &outpost = outposts[outpost_id];

        // Calculate distance from base to outpost
        double distance = calculateDistance(base.x, base.y, outpost.x, outpost.y);

        // Energy required for the round trip
        double energy_used = 2 * distance * uav.energy_per_km;

        // If UAV does not have enough energy, invalid solution
        if (energy_used > uav.total_energy) return numeric_limits<double>::max();

        total_energy += energy_used;
        priority_score += outpost.priority;
    }

    return total_energy - (priority_score * 10); // Higher priority reduces cost
}

// PSO Algorithm
void PSO(vector<UAV> &uavs, vector<Outpost> &outposts, BaseStation &base) {
    vector<Particle> particles(NUM_PARTICLES);

    srand(time(0));

    // Initialize particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
        for (int j = 0; j < uavs.size(); j++) {
            particles[i].assignment.push_back(rand() % outposts.size()); // Random assignment
            particles[i].velocity.push_back((rand() % 10 - 5) / 10.0); // Small random velocity
        }
        particles[i].fitness = fitnessFunction(particles[i], uavs, outposts, base);
    }

    // Global best solution
    Particle best_global = particles[0];

    // PSO Iterations
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        for (auto &particle : particles) {
            // Update fitness
            particle.fitness = fitnessFunction(particle, uavs, outposts, base);

            // Update best global solution
            if (particle.fitness < best_global.fitness) {
                best_global = particle;
            }

            // Update velocity and position
            for (int j = 0; j < uavs.size(); j++) {
                double r1 = (double)rand() / RAND_MAX;
                double r2 = (double)rand() / RAND_MAX;

                particle.velocity[j] = W * particle.velocity[j] +
                                       C1 * r1 * (best_global.assignment[j] - particle.assignment[j]) +
                                       C2 * r2 * (best_global.assignment[j] - particle.assignment[j]);

                particle.assignment[j] += round(particle.velocity[j]);

                // Ensure valid assignments
                if (particle.assignment[j] < 0) particle.assignment[j] = 0;
                if (particle.assignment[j] >= outposts.size()) particle.assignment[j] = outposts.size() - 1;
            }
        }
    }

    // Output best solution
    cout << "\nBest UAV Allocation:\n";
    for (int i = 0; i < uavs.size(); i++) {
        cout << "UAV " << uavs[i].id << " assigned to Outpost " << best_global.assignment[i] << endl;
    }
    cout << "Best Energy Cost: " << best_global.fitness << endl;
}

int main() {
    int n, m;

    // Input number of outposts and UAVs
    cout << "Enter number of outposts: ";
    cin >> n;
    cout << "Enter number of UAVs: ";
    cin >> m;

    vector<UAV> uavs(m);
    vector<Outpost> outposts(n);
    BaseStation base;

    // Input UAV details
    cout << "Enter UAV details (ID, weight capacity, energy/km, total energy):\n";
    for (int i = 0; i < m; i++) {
        cin >> uavs[i].id >> uavs[i].weight_capacity >> uavs[i].energy_per_km >> uavs[i].total_energy;
    }

    // Input Outpost details
    cout << "Enter Outpost details (ID, medicine, food, weapons, x, y, priority):\n";
    for (int i = 0; i < n; i++) {
        cin >> outposts[i].id >> outposts[i].medicine >> outposts[i].food >> outposts[i].weapons
            >> outposts[i].x >> outposts[i].y >> outposts[i].priority;
    }

    // Input Base Station details
    cout << "Enter Base Station coordinates (x y): ";
    cin >> base.x >> base.y;

    // Run PSO Algorithm
    PSO(uavs, outposts, base);

    return 0;
}
