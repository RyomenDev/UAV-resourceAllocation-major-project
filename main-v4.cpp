#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct UAV
{
    int id;
    double weight_capacity, energy_per_km, total_energy;
};

struct Outpost
{
    int id;
    double medicine, food, weapons, x, y;
    int priority;
};

struct BaseStation
{
    double x, y;
};

// Function to calculate distance
double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Particle Swarm Optimization Particle
struct Particle
{
    vector<int> assignment;
    double fitness;

    Particle(int numUAVs)
    {
        assignment.resize(numUAVs, -1); // -1 means not assigned
        fitness = numeric_limits<double>::max();
    }
};

// Fitness Function
double fitnessFunction(const Particle &p, const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base)
{
    double total_energy = 0;
    vector<bool> assigned(outposts.size(), false);

    for (int i = 0; i < p.assignment.size(); i++)
    {
        int outpost_id = p.assignment[i];
        if (outpost_id == -1 || assigned[outpost_id])
            continue; // Ensure unique assignments

        assigned[outpost_id] = true;
        const UAV &uav = uavs[i];
        const Outpost &outpost = outposts[outpost_id];

        double distance = calculateDistance(base.x, base.y, outpost.x, outpost.y);
        double energy_used = 2 * distance * uav.energy_per_km;

        if (energy_used > uav.total_energy)
            return numeric_limits<double>::max();

        total_energy += energy_used;
        total_energy += (100 / (outpost.priority + 1)); // Penalize lower-priority outposts less
    }

    return total_energy;
}

// Randomly Initialize Particles
void initializeParticles(vector<Particle> &particles, int numParticles, int numUAVs, int numOutposts)
{
    for (int i = 0; i < numParticles; i++)
    {
        Particle p(numUAVs);
        for (int j = 0; j < numUAVs; j++)
        {
            p.assignment[j] = rand() % numOutposts;
        }
        particles[i] = p;
    }
}

// Particle Swarm Optimization Algorithm
Particle PSO(int numParticles, int numIterations, const vector<UAV> &uavs, const vector<Outpost> &outposts, const BaseStation &base)
{
    vector<Particle> particles(numParticles, Particle(uavs.size()));
    initializeParticles(particles, numParticles, uavs.size(), outposts.size());

    Particle globalBest = particles[0];
    globalBest.fitness = fitnessFunction(globalBest, uavs, outposts, base);

    for (int iter = 0; iter < numIterations; iter++)
    {
        for (Particle &p : particles)
        {
            p.fitness = fitnessFunction(p, uavs, outposts, base);
            if (p.fitness < globalBest.fitness)
            {
                globalBest = p;
            }
        }

        // Update particle positions
        for (Particle &p : particles)
        {
            for (int j = 0; j < p.assignment.size(); j++)
            {
                if (rand() % 2 == 0)
                {
                    p.assignment[j] = rand() % outposts.size(); // Randomly change assignment
                }
            }
        }
    }

    return globalBest;
}

// Main Function
int main()
{
    srand(time(0));

    int numOutposts, numUAVs;
    cout << "Enter number of outposts: ";
    cin >> numOutposts;

    cout << "Enter number of UAVs: ";
    cin >> numUAVs;

    vector<UAV> uavs(numUAVs);
    cout << "Enter UAV details (ID, weight capacity, energy/km, total energy):" << endl;
    for (int i = 0; i < numUAVs; i++)
    {
        cin >> uavs[i].id >> uavs[i].weight_capacity >> uavs[i].energy_per_km >> uavs[i].total_energy;
    }

    vector<Outpost> outposts(numOutposts);
    cout << "Enter Outpost details (ID, medicine, food, weapons, x, y, priority):" << endl;
    for (int i = 0; i < numOutposts; i++)
    {
        cin >> outposts[i].id >> outposts[i].medicine >> outposts[i].food >> outposts[i].weapons >> outposts[i].x >> outposts[i].y >> outposts[i].priority;
    }

    BaseStation base;
    cout << "Enter Base Station coordinates (x y): ";
    cin >> base.x >> base.y;

    Particle bestSolution = PSO(30, 100, uavs, outposts, base);

    cout << "\nBest UAV Allocation:\n";
    for (int i = 0; i < bestSolution.assignment.size(); i++)
    {
        cout << "UAV " << uavs[i].id << " assigned to Outpost " << outposts[bestSolution.assignment[i]].id << endl;
    }

    cout << "Best Energy Cost: " << bestSolution.fitness << endl;

    return 0;
}
