#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Constants for priority calculation weights
const double ALPHA = 0.5; // Weight for resource urgency
const double BETA = 0.3;  // Weight for distance (inverted)
const double GAMMA = 0.2; // Weight for criticality level

// Structure for UAVs
struct UAV
{
    int id;
    double weight_capacity;
    double energy_per_km;
    double total_energy;
};

// Structure for Outposts
struct Outpost
{
    int id;
    double medicine;
    double food;
    double weapons;
    double x, y;
    double priority; // Calculated dynamically
};

// Structure for Base Station
struct BaseStation
{
    double x, y;
};

// Function to calculate Euclidean distance
double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to calculate priority for an outpost
double calculatePriority(const Outpost &outpost, const BaseStation &base)
{
    double resource_urgency = outpost.medicine + outpost.food + outpost.weapons;
    double distance = calculateDistance(base.x, base.y, outpost.x, outpost.y);

    // Avoid division by zero
    double distance_factor = (distance > 0) ? (1.0 / distance) : 1.0;

    return ALPHA * resource_urgency + BETA * distance_factor + GAMMA * outpost.priority;
}

// Particle for PSO
struct Particle
{
    vector<int> position; // UAV assignments
    double fitness;
    vector<int> best_position;
    double best_fitness;
};

// Function to initialize particles for PSO
void initializeParticles(vector<Particle> &swarm, int num_particles, int num_uavs, int num_outposts)
{
    srand(time(0));
    for (int i = 0; i < num_particles; i++)
    {
        Particle p;
        for (int j = 0; j < num_uavs; j++)
        {
            p.position.push_back(rand() % num_outposts); // Random UAV to Outpost mapping
        }
        p.fitness = numeric_limits<double>::max();
        p.best_position = p.position;
        p.best_fitness = p.fitness;
        swarm.push_back(p);
    }
}

// Fitness function to evaluate UAV allocation
double fitnessFunction(const vector<int> &assignment, const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base)
{
    double total_energy_cost = 0.0;

    for (size_t i = 0; i < assignment.size(); i++)
    {
        int outpost_id = assignment[i];
        const Outpost &outpost = outposts[outpost_id];
        const UAV &uav = uavs[i];

        double distance = calculateDistance(base.x, base.y, outpost.x, outpost.y);
        double energy_required = distance * uav.energy_per_km;

        if (energy_required > uav.total_energy || outpost.priority == 0)
        {
            return numeric_limits<double>::max(); // Invalid assignment
        }

        total_energy_cost += energy_required / outpost.priority; // Lower cost for high-priority outposts
    }

    return total_energy_cost;
}

// PSO Algorithm
vector<int> pso(const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base, int num_particles, int iterations)
{
    vector<Particle> swarm;
    initializeParticles(swarm, num_particles, uavs.size(), outposts.size());

    vector<int> global_best_position = swarm[0].position;
    double global_best_fitness = numeric_limits<double>::max();

    for (int iter = 0; iter < iterations; iter++)
    {
        for (auto &particle : swarm)
        {
            particle.fitness = fitnessFunction(particle.position, uavs, outposts, base);

            if (particle.fitness < particle.best_fitness)
            {
                particle.best_fitness = particle.fitness;
                particle.best_position = particle.position;
            }

            if (particle.fitness < global_best_fitness)
            {
                global_best_fitness = particle.fitness;
                global_best_position = particle.position;
            }
        }

        // Update particles (basic PSO inertia + velocity update)
        for (auto &particle : swarm)
        {
            for (size_t i = 0; i < particle.position.size(); i++)
            {
                if (rand() % 2)
                {
                    particle.position[i] = particle.best_position[i];
                }
                else
                {
                    particle.position[i] = global_best_position[i];
                }
            }
        }
    }

    return global_best_position;
}

int main()
{
    int n, m;
    cout << "Enter number of outposts: ";
    cin >> n;
    cout << "Enter number of UAVs: ";
    cin >> m;

    vector<UAV> uavs(m);
    vector<Outpost> outposts(n);
    BaseStation base;

    // Input UAV details
    cout << "Enter UAV details (ID, weight capacity, energy/km, total energy):\n";
    for (int i = 0; i < m; i++)
    {
        cin >> uavs[i].id >> uavs[i].weight_capacity >> uavs[i].energy_per_km >> uavs[i].total_energy;
    }

    // Input Outpost details
    cout << "Enter Outpost details (ID, medicine, food, weapons, x, y, priority level 1-5):\n";
    for (int i = 0; i < n; i++)
    {
        cin >> outposts[i].id >> outposts[i].medicine >> outposts[i].food >> outposts[i].weapons >> outposts[i].x >> outposts[i].y >> outposts[i].priority;

        outposts[i].priority = calculatePriority(outposts[i], base);
    }

    // Input Base Station coordinates
    cout << "Enter Base Station coordinates (x y): ";
    cin >> base.x >> base.y;

    // Run PSO
    vector<int> best_allocation = pso(uavs, outposts, base, 50, 100);

    // Output best UAV allocation
    cout << "\nBest UAV Allocation:\n";
    for (size_t i = 0; i < best_allocation.size(); i++)
    {
        cout << "UAV " << uavs[i].id << " assigned to Outpost " << outposts[best_allocation[i]].id << endl;
    }

    cout << "Best Energy Cost: " << fitnessFunction(best_allocation, uavs, outposts, base) << endl;

    return 0;
}
